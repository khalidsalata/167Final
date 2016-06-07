//
//  Pod.cpp
//  167Proj3
//
//  Created by adboom on 4/29/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include "OBJObject.h"
#include "Window.h"
Pod::Pod(){
<<<<<<< HEAD
    this->p = new OBJObject("rock1.obj");
}

void Pod::draw(GLuint shaderProgram){
    this->p->draw(glm::mat4(1.0f), 1, &shaderProgram);
=======
    system("pwd");
    if(Window::khalid){
        this->p = new OBJObject("/Users/adboom/Downloads/skybox/rock1.obj");
    } else {
        this->p = new OBJObject("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/rock1.obj");
    }
}
void Pod::draw(glm::mat4 C){
    glm::mat4 temp = M * C;
    this->p->draw(temp, 1);
}

void Pod::update(glm::mat4 Up){
    M = Up;
    //this->p->toWorld = glm::rotate(temp, 0.0001f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
}


