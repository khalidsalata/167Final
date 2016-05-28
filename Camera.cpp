//
//  Camera.cpp
//  167Proj3
//
//  Created by adboom on 5/5/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include <string.h>
#include "OBJObject.h"

Camera::Camera(){
    M = glm::mat4(1.0f);
}

void Camera::draw(glm::mat4 C){
    //M = C;
}

void Camera::update(glm::mat4 U){
    M = U;
}