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
        bigBuf.push_back(textures[i].x);
        bigBuf.push_back(textures[i].y);
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
    boundBox = new boundingBox(minxg, minyg, minzg, maxxg, maxyg, maxzg);
    name = filepath;
<<<<<<< HEAD
    
=======
    if(Window::khalid){
        objShade = LoadShaders("/Users/adboom/Downloads/skybox/objShader.vert", "/Users/adboom/Downloads/skybox/objShader.frag");
    } else {
        objShade = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.frag");
    }
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
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
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    
<<<<<<< HEAD
    //Get ready for some texture shit
    glGenTextures(1, &textureID);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    unsigned char * image;
    int width = 512;
    int height = 512;
    std::string path = "/Users/adboom/Downloads/";
    image = loadPPM((path + "rock_texture_jpg_phpfPp0Ku.ppm").c_str(), width, height);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Use bilinear interpolation:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Use clamp to edge to hide skybox edges:
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    
    
    //We're done, we can unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
=======
//    //Get ready for some texture shit
//    glGenTextures(1, &textureID);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    
//    // Make sure no bytes are padded:
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    
//    unsigned char * image;
//    int width = 512;
//    int height = 512;
//    std::string path = "/Users/adboom/Downloads/skybox/";
//        
//    // Select GL_MODULATE to mix texture with polygon color for shading:
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    
//    // Use bilinear interpolation:
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    // Use clamp to edge to hide skybox edges:
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    
//    //glEnable(GL_CULL_FACE);
//    //glCullFace(GL_BACK);
//    
//    
//    //We're done, we can unbind the texture
//    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//    
//    
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959

    
    
}

OBJObject::~OBJObject(){
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void OBJObject::parse(const char *filepath)
{
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
    minX = minY = minZ = FLT_MAX;
    maxX = maxY = maxZ = FLT_MIN;
    while (getline(myFile,line)){
        if(line[0] == 'v' || line[0] == 'f'){
            std::istringstream buffer(line);
            std::vector<std::string> toks;
            
            std::copy(std::istream_iterator<std::string>(buffer),
                      std::istream_iterator<std::string>(),
                      std::back_inserter(toks));
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
            else if(toks[0] == "vt"){
                this->textures.push_back(glm::vec2(x, y));
            }
            if(line[0] == 'f'){
<<<<<<< HEAD
                unsigned long pos = toks[1].find("/");
                unsigned int v = stoi(toks[1].substr(0,pos));
                this->indices.push_back(v-1);
                pos = toks[2].find("/");
                v = stoi(toks[2].substr(0,pos));
                this->indices.push_back(v-1);
                pos = toks[3].find("/");
                v = stoi(toks[3].substr(0,pos));
                this->indices.push_back(v-1);
                pos = toks[1].find("/");
                v = stoi(toks[1].substr(0,pos));
                this->indices.push_back(v-1);
                pos = toks[3].find("/");
                v = stoi(toks[3].substr(0,pos));
                this->indices.push_back(v-1);
                pos = toks[4].find("/");
                v = stoi(toks[4].substr(0,pos));
                this->indices.push_back(v-1);
                shapeCount = shapeCount + 2;
=======
                for(int i = 1; i < 5; i++){
                    unsigned long pos = toks[i].find("/");
                    unsigned int v = stoi(toks[i].substr(0,pos));
                    cout<<":"<<v<<endl;
                    this->indices.push_back(v-1);
                }
                shapeCount++;
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
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
    //Align with globals
    maxxg = maxX/maxDel;
    minxg = minX/maxDel;
    minyg = minY/maxDel;
    maxyg = maxY/maxDel;
    minzg = minZ/maxDel;
    maxzg = maxZ/maxDel;
    
    
    for(int i = 0; i < this->vertices.size(); i++){
        glm::vec3& name = this->vertices[i];
        this->vertices[i] = glm::vec3((name.x - avgX)/maxDel, (name.y - avgY)/maxDel, (name.z - avgZ)/maxDel);
    }
    
    printf("%s is done\n", filepath);
    printf("%lu vectors and %lu vector normals\n", vertices.size(), normals.size());
    myFile.close();   // make sure you don't forget to close the file when done
    printf("There are %d triangles\n", shapeCount);
    
    
    
}

void OBJObject::draw(glm::mat4 C, int type, GLuint* shader)
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
    glUseProgram(*shader);
    
    
    glUniform1i(glGetUniformLocation(*shader, "ourTexture"), 2);
    GLuint MatrixID = glGetUniformLocation(*shader, "MVP");
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
   
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(VAO);
    glDrawElements(GL_QUADS, this->facecount * 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
    
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
    float newminzg = boundBox->getMinZ() + tv.z;
    float newmaxzg = boundBox->getMaxZ() + tv.z;
    float newminyg = boundBox->getMinY() + tv.y;
    float newmaxyg = boundBox->getMaxY() + tv.y;
    float newminxg = boundBox->getMinX() + tv.x;
    float newmaxxg = boundBox->getMaxX() + tv.x;
    boundBox->update(newminxg, newminyg, newminzg, newmaxxg, newmaxyg, newmaxzg);
}

void OBJObject::hardTranslate(glm::vec3 tv){
    toWorld[3] = glm::vec4(tv, 1.0f);
    float newminzg = minzg + tv.z;
    float newmaxzg = maxzg + tv.z;
    float newminyg = minyg + tv.y;
    float newmaxyg = maxyg + tv.y;
    float newminxg = minxg + tv.x;
    float newmaxxg = maxxg + tv.x;
    boundBox->update(newminxg, newminyg, newminzg, newmaxxg, newmaxyg, newmaxzg);

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
    minzg = minzg * sv.z;
    maxzg = maxzg * sv.z;
    minyg = minyg * sv.y;
    maxyg = maxyg * sv.y;
    minxg = minxg * sv.x;
    maxxg = maxxg * sv.x;
    boundBox->update(minxg, minyg, minzg, maxxg, maxyg, maxzg);
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

unsigned char* OBJObject::loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    if ( (fp=fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    // Read width and height:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
}
