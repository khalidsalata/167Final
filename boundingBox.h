//
//  boundingBox.hpp
//  CSE-167-Final
//
//  Created by Il Dottore on 5/31/16.
//  Copyright © 2016 Ahmed Elhosseiny. All rights reserved.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace std;

class boundingBox {
    float minX, minY, minZ, maxX, maxY, maxZ;
    
public:
    glm::mat4 toWorld;
    GLuint bbVAO, bbVBO;
    vector<glm::vec3> vertices;
    vector<GLfloat> bigBuf;
    
    boundingBox();
    ~boundingBox();
    void setMinX(float incX){minX = incX;}
    void setMinY(float incY){minY = incY;}
    void setMinZ(float incZ){minZ = incZ;}

    void setMaxX(float incX){maxX = incX;}
    void setMaxY(float incY){maxY = incY;}
    void setMaxZ(float incZ){maxZ = incZ;}

    float getMinX() { return minX; }
    float getMinY() { return minY; }
    float getMinZ() { return minZ; }
    
    float getMaxX() { return maxX; }
    float getMaxY() { return maxY; }
    float getMaxZ() { return maxZ; }
    
    void draw(GLuint);
    void genBigBuf();
    void update(float, float, float, float, float, float);
    void mtranslate(glm::vec3);
    void scale(glm::vec3);
};
#endif