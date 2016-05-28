//
//  Point.cpp
//  167Proj4
//
//  Created by adboom on 5/13/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include "window.h"

Point::Point(glm::vec4 posC, int idC){
    pos = posC;
    id = idC;
    M = glm::mat4(1.0f);
    
    selShade = LoadShaders("/Users/adboom/Downloads/skybox/selection.vert", "/Users/adboom/Downloads/skybox/selection.frag");
    pointShade = LoadShaders("/Users/adboom/Downloads/skybox/pointShader.vert", "/Users/adboom/Downloads/skybox/pointShader.frag");
//    selShade = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/selection.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/selection.frag");
//    pointShade = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/pointShader.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/pointShader.frag");
    update(glm::mat4(1.0f));
    
}

void Point::draw(glm::mat4 C, int sel){
    
    glm::mat4 MVP = Window::P * Window::V * M;
    glPointSize(10.0f);
    if(sel == 1){
        glUseProgram(selShade);
        GLuint idID = glGetUniformLocation(selShade, "id");
        glUniform1ui(idID, id);
        glPointSize(25.0f);
    }
    else{ glUseProgram(pointShade); }
    
    GLuint MatrixID = glGetUniformLocation(selShade, "MVP");
    GLuint modID = glGetUniformLocation(selShade,"model");
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modID, 1, GL_FALSE, &M[0][0]);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void Point::draw(glm::mat4 C){
    
}

void Point::update(glm::mat4 U){
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    std::vector<GLfloat> bigBuf;
    bigBuf.push_back(pos.x);
    bigBuf.push_back(pos.y);
    bigBuf.push_back(pos.z);
    bigBuf.push_back(pos.w);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void Point::move(glm::vec4 toPoint){
    pos = pos + toPoint;
    M = glm::translate(glm::mat4(1.0f), glm::vec3(toPoint)) * M;
   }

void Point::waitMove(glm::vec4 toPoint){
    //printf("Topoint: %f, %f, %f\n", toPoint.x, toPoint.y, toPoint.z);
    pos = pos + toPoint;
    M = glm::translate(glm::mat4(1.0f), glm::vec3(toPoint)) * M;
    }

void Point::moveTo(glm::vec4 toPoint){
    glm::vec4 temp = toPoint - pos;
    pos = toPoint;
    M = glm::translate(glm::mat4(1.0f), glm::vec3(temp));
}

