#include "OBJObject.h"
#include "Window.h"
#include "Cube.h"
#include <fstream>
#include <string>
#include <sstream>
#include <errno.h>
#include <iostream>
using namespace std;

std::map<const char*, std::vector< std::vector<glm::vec3> > > OBJObject::perstV = std::map<const char*, std::vector< std::vector<glm::vec3> > >();
std::map<const char*, std::vector<GLuint> > OBJObject::perstIn = std::map<const char*, std::vector<GLuint> >();
std::map<const char*, int> OBJObject::perstCount = std::map<const char*, int>();

void OBJObject::genBigBuf()
{
    for(int i = 0; i < vertices.size(); i++){
        bigBuf.push_back(vertices[i].x);
        bigBuf.push_back(vertices[i].y);
        bigBuf.push_back(vertices[i].z);
        bigBuf.push_back(normals[i].x);
        bigBuf.push_back(normals[i].y);
        bigBuf.push_back(normals[i].z);
    }
}

void OBJObject::setExpo(float jump){ expo = expo + jump; }


OBJObject::OBJObject(const char *filepath)
{
    this->angle = 0.0f;
    this->facecount = 0;
    expo = 100.0f;
    tempW = toWorld = glm::mat4(1.0f);
    parse(filepath);
    name = filepath;
    objShade = LoadShaders("/Users/adboom/Desktop/167Proj3/167Proj3/objShader.vert", "/Users/adboom/Desktop/167Proj3/167Proj3/objShader.frag");
    
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    GLuint* i = &indices[0];
    
    genBigBuf();
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), i, GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

OBJObject::~OBJObject(){
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void OBJObject::parse(const char *filepath)
{
   if(perstIn.count(filepath) > 0 && perstV.count(filepath) > 0){
       printf("Using previous data\n");
       vertices = perstV[filepath][0];
       normals = perstV[filepath][1];
       indices = perstIn[filepath];
       facecount = perstCount[filepath];
       return;
    }
    
    GLfloat x,y,z;  // vertex coordinates
    ifstream myFile(filepath);  // make the file name configurable so you can load other files
    if (myFile.is_open() == false) {
        int errsv = errno;
        std::cerr << "error loading file with errno: " + to_string(errsv) << std::endl; exit(-1);
    }  // just in case the file can't be found or is corrupt
    //printf("%s loading...", filepath);
    string line;
    int count = 1;
    
    int shapeCount = 1;
    GLfloat minX, minY, minZ, maxX, maxY, maxZ;
    minX = minY = minZ = FLT_MAX;
    maxX = maxY = maxZ = FLT_MIN;
    while (getline(myFile,line)){
        if(line[0] == 'v' || line[0] == 'f'){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> toks(beg, end);
            x = stof(toks[1]);
            y = stof(toks[2]);
            z = stof(toks[3]);
            if(toks[0] == "v"){
                if (x > maxX) { maxX = x; }
                else if (x < minX) { minX = x; }
                if (y > maxY) { maxY = y; }
                else if (y < minY) { minY = y; }
                if (z > maxZ) { maxZ = z; }
                else if (z < minZ) { minZ = z; }
                this->vertices.push_back({x, y, z});
                
            }
            else if(toks[0] == "vn"){
                glm::vec3 colors = glm::normalize(glm::vec3({x, y, z}));
                colors = (colors * glm::vec3(1,1,1))/glm::vec3(2,2,2);
                this->normals.push_back(colors);
            }
            if(line[0] == 'f'){
                for(int i = 1; i < 4; i++){
                    unsigned long pos = toks[i].find("//");
                    unsigned int v = stoi(toks[i].substr(0,pos));
                    this->indices.push_back(v-1);
                }
                shapeCount++;
            }
            else{ count++; }
        }
        // read normal data accordingly
    }
    
    this->facecount = shapeCount;
    
    GLfloat deltaX = maxX - minX;
    GLfloat deltaY = maxY - minY;
    GLfloat deltaZ = maxZ - minZ;
    GLfloat avgX = (minX + maxX)/2.0;
    GLfloat avgY = (minY + maxY)/2.0;
    GLfloat avgZ = (minZ + maxZ)/2.0;
    GLfloat maxDel;
    
    if(deltaX > deltaY) { maxDel = deltaX; }
    else { maxDel = deltaY; }
    
    if(maxDel < deltaZ) { maxDel = deltaZ; }
    
    for(int i = 0; i < this->vertices.size(); i++){
        glm::vec3& name = this->vertices[i];
        this->vertices[i] = glm::vec3((name.x - avgX)/maxDel, (name.y - avgY)/maxDel, (name.z - avgZ)/maxDel);
    }
    
    printf("%s is done\n", filepath);
    printf("%lu vectors and %lu vector normals\n", vertices.size(), normals.size());
    myFile.close();   // make sure you don't forget to close the file when done
    printf("There are %d triangles\n", shapeCount);
    
    std::vector< std::vector<glm::vec3> > in = { vertices, normals };
    
    perstV[filepath] = in;
    perstIn[filepath] = indices;
    perstCount[filepath] = shapeCount;
    
}

void OBJObject::draw(glm::mat4 C, int type)
{
    glm::mat4 temp = C * toWorld;
    //temp = glm::rotate(temp, 0.02f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    // Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
    glm::mat4 MVP = Window::P * Window::V * temp;
    // We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    
    // Clear the color and depth buffers
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use the shader of programID
    glUseProgram(objShade);
    
    
    GLuint MatrixID = glGetUniformLocation(objShade, "MVP");
    GLuint modID = glGetUniformLocation(objShade,"model");
    GLuint invID = glGetUniformLocation(objShade,"invModel");
    glm::mat4 invTo = glm::inverse(temp);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modID, 1, GL_FALSE, &temp[0][0]);
    glUniformMatrix4fv(invID, 1, GL_FALSE, &invTo[0][0]);
    
    glUniform1i(glGetUniformLocation(objShade, "skybox"), 0);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, this->facecount * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    //tempW = glm::mat4(1.0f);
}

void OBJObject::update(int dir){
    if(dir > 0 && dir < 7){
        translate(dir);
    }
    else if(dir == 7 || dir == 8){
        scale(dir);
    }
    else if(dir == 9 || dir == 10){
        orbit(dir);
    }
    else if(dir == 11){
        toWorld = glm::mat4(1.0f);
    }
    dir = 0;
    //spin(0.1f);
}

void OBJObject::spin(float deg){
    this->angle += deg;
    if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
    // This creates the matrix to rotate the cube
    toWorld = glm::rotate(toWorld, 0.01f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void OBJObject::translate(int dir){
    switch (dir) {
        case 1:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * toWorld;
            break;
        case 2:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * toWorld;
            break;
        case 3:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * toWorld;
            break;
        case 4:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * toWorld;
            break;
        case 5:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f)) * toWorld;
            break;
        case 6:
            toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * toWorld;
            break;
        default:
            break;
    }
}

void OBJObject::mtranslate(glm::vec3 tv){
    toWorld = glm::translate(glm::mat4(1.0f), tv) * toWorld;
}

void OBJObject::scale(int dir){
    switch (dir){
        case 7:
            toWorld = glm::scale(toWorld, glm::vec3(0.5f, 0.5f, 0.5f));
            break;
        case 8:
            toWorld = glm::scale(toWorld, glm::vec3(1.5f, 1.5f, 1.5f));
            break;
        default:
            break;
    }
}

void OBJObject::scale(glm::vec3 sv){
    toWorld = glm::scale(toWorld, sv);
}

void OBJObject::orbit(int dir){
    switch (dir){
        case 9:
            toWorld = glm::rotate(glm::mat4(1.0f), 0.1f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f)) * toWorld;
            break;
        case 10:
            toWorld = glm::rotate(glm::mat4(1.0f), -0.1f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f)) * toWorld;
            break;
        default:
            break;
    }
    
}

void OBJObject::selforbit(float deg, glm::vec3 rv){
    toWorld = glm::rotate(toWorld, deg * glm::pi<float>(), rv);
}


void OBJObject::morbit(glm::vec3 rt, float deg){
    toWorld = glm::rotate(glm::mat4(1.0f), deg * glm::pi<float>(), rt) * toWorld;
}
