//
//  Group.cpp
//  167Proj3
//
//  Created by adboom on 4/29/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#include <stdio.h>
#include "SceneGraph.h"
#include "OBJObject.h"


Group::Group(){
    this->nodes = std::list<Node*>();
}

void Group::addChild(Node * n){
    this->nodes.push_back(n);
}

void Group::addChildren(std::vector<Node *> cn){
    for(int x = 0; x < this->nodes.size(); x++){
        this->addChild(cn[x]);
    }
}

void Group::removeChild(){
    this->nodes.pop_back();
}

void Group::draw(glm::mat4 C){
    std::list<Node*>::iterator it;
    for(it = this->nodes.begin(); it != nodes.end(); ++it){
        (*it)->draw(C);
    }
}

void Group::update(glm::mat4 Up){
    std::list<Node*>::iterator it;
    for(it = this->nodes.begin(); it != nodes.end(); ++it){
        (*it)->update(Up * this->U);
    }
}
