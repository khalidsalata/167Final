//
//  Drops.cpp
//  167Final
//
//  Created by adboom on 6/7/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include "window.h"


Drops::Drops(glm::vec3 source, bool excessive){
    time = 0.0f;
    origin = source;
    int ex = 1;
    if(excessive){
        ex = 250;
    }
    
    glm::vec3 sv;
    for(int x = 0; x < (ex * 8); x++){
        droplets.push_back(source);
    }
    
    
    //Set velocities as vectors
    for(int i = 0; i < ex; i++){
        float bi = i/250.0f;
        float y = 1 + (i/100.0f);
        vels.push_back(glm::normalize(glm::vec3(-1.0f, y, -1.0f)));
        vels.push_back(glm::normalize(glm::vec3(0.0f, y, -1.0f)));
        vels.push_back(glm::normalize(glm::vec3(1.0f, y, -1.0f)));
        vels.push_back(glm::normalize(glm::vec3(-1.0f, y, 0.0f)));
        vels.push_back(glm::normalize(glm::vec3(1.0f, y, 0.0f)));
        vels.push_back(glm::normalize(glm::vec3(-1.0f, y, 1.0f)));
        vels.push_back(glm::normalize(glm::vec3(0.0f, y, 1.0f)));
        vels.push_back(glm::normalize(glm::vec3(1.0f, y, 1.0f)));
    }
    
    printf("Size of %lu\n", droplets.size());
    printf("Size of %lu\n", vels.size());
    
    genBigBuf();
    
    printf("Size of %lu\n", bigBuf.size());
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void Drops::move(){
    time = time + 0.0015f;
    
    //Apply acceleration on velocities
    for(int i = 0; i < vels.size(); i++){
        vels[i].y = vels[i].y + (-0.9f * time);
        vels[i] = glm::normalize(vels[i]);
    }
    
    //Apply velocity on positions
    for(int i = 0; i < droplets.size(); i++){
        droplets[i] = droplets[i] + (time * vels[i]);
    }
    
    update();
}

void Drops::draw(GLint shader){
    glm::mat4 MVP = Window::P * Window::V;
    glUseProgram(shader);
    
    GLuint MatrixID = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glLineWidth(50.0f);
    glPointSize(5.0f);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, (int) droplets.size());
    glBindVertexArray(0);

}

void Drops::update(){
    // Create buffers/arrays
    
    this->bigBuf.clear();
    
    genBigBuf();
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}


void Drops::genBigBuf(){
    for(int x = 0; x < droplets.size(); x++){
        bigBuf.push_back(droplets[x].x);
        bigBuf.push_back(droplets[x].y);
        bigBuf.push_back(droplets[x].z);
    }
}
