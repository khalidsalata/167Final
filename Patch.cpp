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

Patch::Patch(std::vector<glm::vec4> points){
    
    for(int i = 0; i < 16; i++){
        cps.push_back(points[i]);
    }
    
    B[0] = glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f);
    B[1] = glm::vec4(3.0f, -6.0f, 3.0f, 0.0f);
    B[2] = glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f);
    B[3] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    
    setControl();
    
    if(Window::khalid){
    patchShade = LoadShaders("/Users/adboom/Downloads/skybox/objShader.vert", "/Users/adboom/Downloads/skybox/objShader.frag");
    } else {
    patchShade = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/objShader.frag");
    }
    makeCurves();
    genBigBuf();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void Patch::draw(glm::mat4 C){
    glm::mat4 MVP = Window::P * Window::V * C;
    glm::mat4 temp = glm::mat4(1.0f);
    glUseProgram(patchShade);
    GLuint MatrixID = glGetUniformLocation(patchShade, "MVP");
    GLuint modID = glGetUniformLocation(patchShade,"model");
    GLuint invID = glGetUniformLocation(patchShade,"invModel");
    glm::mat4 invTo = glm::inverse(temp);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modID, 1, GL_FALSE, &temp[0][0]);
    glUniformMatrix4fv(invID, 1, GL_FALSE, &invTo[0][0]);
   
    
    glLineWidth(50.0f);
    glPointSize(5.0f);
    
    //printf("Vertices size: %lu\n", vertices.size());
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 58800);
    glBindVertexArray(0);
    
    
   }

void Patch::update(glm::mat4 Up){
    
}

void Patch::update(){
    // Create buffers/arrays
    this->vertices.clear();
    this->bigBuf.clear();
    makeCurves();
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
    float u = 0.0f;
    for(int m = 0; m < 100; m++){
        glm::vec4 uvec = glm::vec4(pow(u, 3), pow(u, 2), u, 1.0f);
        float v = 0.0f;
        for(int i = 0; i < 100; i++){
            glm::vec4 vvec = glm::vec4(pow(v, 3), pow(v, 2), v, 1.0f);
            float prex = glm::dot(vvec, Cx * uvec);
            float prey = glm::dot(vvec, Cy * uvec);
            float prez = glm::dot(vvec, Cz * uvec);
            this->vertices.push_back(glm::vec3(prex, prey, prez));
            v = v + 0.01f;
        }
        u = u + 0.01f;
    }
    printf("There are %lu vertices\n", vertices.size());
    for(int i = 0; i < vertices.size(); i++){
        glm::vec3 utan, vtan;
        if(i % 100 == 99){
            utan = vertices[i - 1] - vertices[i];
        }
        else{ utan = vertices[i + 1] - vertices[i]; }
        if(i >= 9900){
            vtan = vertices[i - 100] - vertices[i];
        }
        else{ vtan = vertices[i + 100] - vertices[i]; }
        glm::vec3 norm = glm::cross(utan, vtan);
        normals.push_back(norm);
    }
    printf("There are %lu normals\n", normals.size());
}

glm::vec4 Patch::getPoint(float t, glm::vec4 p0, glm::vec4 p1, glm::vec4 p2, glm::vec4 p3){
    glm::mat4 control = glm::mat4(p0, p1, p2, p3);
    
    glm::vec4 cs = glm::vec4(cZero(t), cOne(t), cTwo(t), cThree(t));
    glm::vec4 temp = control * cs;
    return temp;
}

void Patch::genBigBuf()
{
    for(int i = 0; i < vertices.size(); i++){
        if(i % 100 != 99){
            bigBuf.push_back(vertices[i].x);
            bigBuf.push_back(vertices[i].y);
            bigBuf.push_back(vertices[i].z);
            bigBuf.push_back(normals[i].x);
            bigBuf.push_back(normals[i].y);
            bigBuf.push_back(normals[i].z);
        
            bigBuf.push_back(vertices[i + 100].x);
            bigBuf.push_back(vertices[i + 100].y);
            bigBuf.push_back(vertices[i + 100].z);
            bigBuf.push_back(normals[i + 100].x);
            bigBuf.push_back(normals[i + 100].y);
            bigBuf.push_back(normals[i + 100].z);
        
            bigBuf.push_back(vertices[i + 101].x);
            bigBuf.push_back(vertices[i + 101].y);
            bigBuf.push_back(vertices[i + 101].z);
            bigBuf.push_back(normals[i + 101].x);
            bigBuf.push_back(normals[i + 101].y);
            bigBuf.push_back(normals[i + 101].z);
            
            bigBuf.push_back(vertices[i].x);
            bigBuf.push_back(vertices[i].y);
            bigBuf.push_back(vertices[i].z);
            bigBuf.push_back(normals[i].x);
            bigBuf.push_back(normals[i].y);
            bigBuf.push_back(normals[i].z);
            
            bigBuf.push_back(vertices[i + 1].x);
            bigBuf.push_back(vertices[i + 1].y);
            bigBuf.push_back(vertices[i + 1].z);
            bigBuf.push_back(normals[i + 1].x);
            bigBuf.push_back(normals[i + 1].y);
            bigBuf.push_back(normals[i + 1].z);
            
            bigBuf.push_back(vertices[i + 101].x);
            bigBuf.push_back(vertices[i + 101].y);
            bigBuf.push_back(vertices[i + 101].z);
            bigBuf.push_back(normals[i + 101].x);
            bigBuf.push_back(normals[i + 101].y);
            bigBuf.push_back(normals[i + 101].z);
         
        }
        
    }
}

void Patch::setIds(int i1, int i2, int i3, int i4){
    
}
