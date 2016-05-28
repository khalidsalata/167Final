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

Pod::Pod(){
    system("pwd");
    this->p = new OBJObject("rock1.obj");
}

void Pod::draw(glm::mat4 C){
    glm::mat4 temp = M * C;
    this->p->draw(temp, 1);
}

void Pod::update(glm::mat4 Up){
    M = Up;
    //this->p->toWorld = glm::rotate(temp, 0.0001f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}


