//
//  MatrixTransform.cpp
//  167Proj3
//
//  Created by adboom on 5/1/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"

MatrixTransform::MatrixTransform(glm::mat4 toM){
    this->M = toM;
}

MatrixTransform::MatrixTransform(){
    this->M = glm::mat4(1.0f);
}

void MatrixTransform::draw(glm::mat4 C){
    std::list<Node*>::iterator it;
    for(it = this->nodes.begin(); it != nodes.end(); ++it){
        (*it)->draw(C * M);
    }
}

void MatrixTransform::update(glm::mat4 Up){
    M = Up * U * M;
    std::list<Node*>::iterator it;
    for(it = this->nodes.begin(); it != nodes.end(); ++it){
        (*it)->update(U);
    }
}


void MatrixTransform::setUpdate(glm::mat4 Ud){
    this->U = Ud;
}
