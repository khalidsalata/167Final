//
//  Track.cpp
//  167Proj4
//
//  Created by adboom on 5/11/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include "window.h"
#include <math.h>

Patch::Patch(std::vector<glm::vec4> points){
    
    for(int i = 0; i < 16; i++){
        cps.push_back(points[i]);
    }
    
    B[0] = glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f);
    B[1] = glm::vec4(3.0f, -6.0f, 3.0f, 0.0f);
    B[2] = glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f);
    B[3] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    
    up = false;
    
<<<<<<< HEAD
    setControl();
    
=======
    if(Window::khalid){
    patchShade = LoadShaders("/Users/adboom/Downloads/skybox/objShader.vert", "/Users/adboom/Downloads/skybox/objShader.frag");
    } else {
    patchShade = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.frag");
    }
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
    makeCurves();
    genBigBuf();
    makeIndicies();
    
    //At start, current and previous buffers look the same
    preVert = vertices;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    GLuint* i = &indicies[0];
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicies.size(), i, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    
}

void Patch::draw(GLuint shaderProgram){
    glm::mat4 MVP = Window::P * Window::V;
    glm::mat4 tran = glm::mat4(0.5f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.5f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.5f, 0.0f,
                               0.5f, 0.5f, 0.5f, 1.0f);
    glm::mat4 temp = glm::mat4(1.0f);
    glm::mat4 depthBaisMatrix = tran * MVP;
    glUseProgram(shaderProgram);
    
    glUniform1i(glGetUniformLocation(shaderProgram, "refMap"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "shadowMap"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "skybox"), 2);
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    GLuint modID = glGetUniformLocation(shaderProgram,"model");
    GLuint invID = glGetUniformLocation(shaderProgram,"invModel");
    GLuint depthID = glGetUniformLocation(shaderProgram,"depthBaisMVP");
    glm::mat4 invTo = glm::inverse(temp);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modID, 1, GL_FALSE, &temp[0][0]);
    glUniformMatrix4fv(invID, 1, GL_FALSE, &invTo[0][0]);
    glUniformMatrix4fv(depthID, 1, GL_FALSE, &depthBaisMatrix[0][0]);
   
    glLineWidth(50.0f);
    glPointSize(5.0f);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int) indicies.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    
   }

void Patch::update(glm::mat4 Up){
    
}

void Patch::update(bool ripple){
    //Save the verts before making a new buffer
    preVert = vertices;
    
    // Create buffers/arrays
    
    this->bigBuf.clear();
    
    if(ripple == false){
        this->vertices.clear();
        makeCurves();
    }
    genBigBuf();
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void Patch::setControl(){
    Gx[0] = glm::vec4(cps[0].x, cps[4].x, cps[8].x, cps[12].x);
    Gx[1] = glm::vec4(cps[1].x, cps[5].x, cps[9].x, cps[13].x);
    Gx[2] = glm::vec4(cps[2].x, cps[6].x, cps[10].x, cps[14].x);
    Gx[3] = glm::vec4(cps[3].x, cps[7].x, cps[11].x, cps[15].x);
    
    Gy[0] = glm::vec4(cps[0].y, cps[4].y, cps[8].y, cps[12].y);
    Gy[1] = glm::vec4(cps[1].y, cps[5].y, cps[9].y, cps[13].y);
    Gy[2] = glm::vec4(cps[2].y, cps[6].y, cps[10].y, cps[14].y);
    Gy[3] = glm::vec4(cps[3].y, cps[7].y, cps[11].y, cps[15].y);
    
    Gz[0] = glm::vec4(cps[0].z, cps[4].z, cps[8].z, cps[12].z);
    Gz[1] = glm::vec4(cps[1].z, cps[5].z, cps[9].z, cps[13].z);
    Gz[2] = glm::vec4(cps[2].z, cps[6].z, cps[10].z, cps[14].z);
    Gz[3] = glm::vec4(cps[3].z, cps[7].z, cps[11].z, cps[15].z);
    
}

float cZero(float t){ return 1.0f * pow((1.0f - t), 3); }

float cOne(float t){ return 3.0f * t * pow((1.0f - t), 2); }

float cTwo(float t){ return 3.0f * pow(t, 2) * pow((1.0f - t), 1); }

float cThree(float t){ return 1.0f * pow(t, 3); }

void Patch::makeCurves(){
    setControl();
    glm::mat4 Cx = B * Gx * B;
    glm::mat4 Cy = B * Gy * B;
    glm::mat4 Cz = B * Gz * B;
    
    //make vertices
    float u = 0.0f;
    for(int m = 0; m < 100; m++){
        std::vector<glm::vec3> anotha1 = std::vector<glm::vec3>();
        glm::vec4 uvec = glm::vec4(pow(u, 3), pow(u, 2), u, 1.0f);
        float v = 0.0f;
        for(int i = 0; i < 100; i++){
            glm::vec4 vvec = glm::vec4(pow(v, 3), pow(v, 2), v, 1.0f);
            float prex = glm::dot(vvec, Cx * uvec);
            float prey = glm::dot(vvec, Cy * uvec);
            float prez = glm::dot(vvec, Cz * uvec);
            anotha1.push_back(glm::vec3(prex, prey, prez));
            v = v + 0.01f;
        }
        this->vertices.push_back(anotha1);
        u = u + 0.01f;
    }
    //printf("There are %lu verticies\n", vertices.size() * vertices[0].size());
    
    //make normals
    for(int m = 0; m < vertices.size(); m++){
        std::vector<glm::vec3> anotha1 = std::vector<glm::vec3>();
        for(int i = 0; i < vertices[m].size(); i++){
            glm::vec3 utan, vtan;
            if(i % 100 == 99){
                utan = vertices[m][i - 1] - vertices[m][i];
            }
            else{ utan = vertices[m][i + 1] - vertices[m][i]; }
            if(m == vertices.size() - 1){
                vtan = vertices[m - 1][i] - vertices[m][i];
            }
            else{ vtan = vertices[m + 1][i] - vertices[m][i]; }
            glm::vec3 norm = glm::cross(utan, vtan);
            anotha1.push_back(norm);
        }
        this->normals.push_back(anotha1);
    }
    //printf("There are %lu normals\n", normals.size() * normals[0].size());
}

glm::vec4 Patch::getPoint(float t, glm::vec4 p0, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3){
    glm::mat4 control = glm::mat4(p0, p1, p2, p3);
    
    glm::vec4 cs = glm::vec4(cZero(t), cOne(t), cTwo(t), cThree(t));
    glm::vec4 temp = control * cs;
    return temp;
}

void Patch::genBigBuf()
{
    for(int m = 0; m < vertices.size(); m++){
        for(int i = 0; i < vertices[m].size(); i++){
            bigBuf.push_back(vertices[m][i].x);
            bigBuf.push_back(vertices[m][i].y);
            bigBuf.push_back(vertices[m][i].z);
            bigBuf.push_back(normals[m][i].x);
            bigBuf.push_back(normals[m][i].y);
            bigBuf.push_back(normals[m][i].z);
        }
    }
    //printf("Bigbuf size: %lu\n", bigBuf.size());
    
}

void Patch::makeIndicies(){
    //New refactored for handling a 2D vertices array
    for(int i = 0; i < vertices.size() - 1; i++){
        for(int x = 0; x < vertices[i].size() - 1; x++){
            GLuint pos = (i * 100) + x;
            indicies.push_back(pos);
            indicies.push_back(pos + 100);
            indicies.push_back(pos + 101);
            indicies.push_back(pos);
            indicies.push_back(pos + 101);
            indicies.push_back(pos + 1);
        }
    }
    
    
//    printf("Indicies size: %lu\n", indicies.size());
    
}

void Patch::makeRipples(glm::vec3 rip){
    //Interpolate between ends
    rip.x = 50.0f + (rip.x * 5.0f);
    rip.y = 50.0f + (rip.y * 5.0f);
    
    int xcomp = (int) rip.x;
    int ycomp = (int) rip.y;
    float time = rip.z;
    float decay = exp(-time * 0.5f);
    float scale = decay * -cosf(2.0f * glm::pi<float>() * time);
//    printf("xcomp: %d, ycomp: %d\n", xcomp, ycomp);
    vertices[xcomp][ycomp] += normals[xcomp][ycomp] * scale;
    hitNeighbors(xcomp, ycomp, 1, time);
//    glm::vec3 utan, vtan;
//    if(xcomp == 99){
//        utan = vertices[xcomp][ycomp - 1] - vertices[xcomp][ycomp];
//    }
//    else{ utan = vertices[xcomp][ycomp + 1] - vertices[xcomp][ycomp]; }
//    if(ycomp > vertices.size() - 1){
//        vtan = vertices[xcomp - 1][ycomp] - vertices[xcomp][ycomp];
//    }
//    else{ vtan = vertices[xcomp + 1][ycomp] - vertices[xcomp][ycomp]; }
//    glm::vec3 norm = glm::cross(utan, vtan);
//    normals[xcomp][ycomp] = norm;
    
    update(true);
}

/* Neighbors are considered in increasing squares from the click
 * point. If the distance from the click point to the neighbor
 * is within some threshhold close to the level of recursion, then 
 * apply the ripple effect to it. Trying to make ripples circular
 * here...
 */
void Patch::hitNeighbors(int initx, int inity, int level, float time){
    if(level > 15){
      return;
    }
    time  = time - 0.2f;
    float decay = 0.3f * pow(1.3f, -level);
    float scale = decay *  -cosf(2.0f * glm::pi<float>() * time);
    scale = scale * pow(.90, level);
    level++;
    float feel = pow(2, 0.5f)/level;
    for(int x = initx - level; x <= initx + level; x++){
        for(int y = inity - level; y <= inity + level; y++){
            //Use the pythagorean theorem
            float lenx = x - initx;
            float leny = y - inity;
            if(pow((pow(lenx, 2) + pow(leny, 2)), .5) - level < feel){
                if(x < 100 && y < 100 && x > 0 && y > 0){
                vertices[x][y] += normals[x][y] * scale;
                }
            }
        }
    }
    hitNeighbors(initx, inity, level, time);

}

void Patch::splash(glm::vec3 source){
    
}
