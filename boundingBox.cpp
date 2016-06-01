//
//  boundingBox.cpp
//  CSE-167-Final
//
//  Created by Il Dottore on 5/31/16.
//  Copyright © 2016 Ahmed Elhosseiny. All rights reserved.
//

#include "boundingBox.h"

boundingBox::boundingBox()
{
    toWorld = glm::mat4(1.0f);
    // Create buffers/arrays
    glGenVertexArrays(1, &bbVAO);
    glGenBuffers(1, &bbVBO);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(bbVAO);
    
    genBigBuf();
    
    glBindBuffer(GL_ARRAY_BUFFER, bbVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bigBuf.size(), &bigBuf[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

boundingBox::~boundingBox()
{
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &bbVAO);
    glDeleteBuffers(1, &bbVBO);
}

void boundingBox::draw(GLuint shaderProgram)
{
    // Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
    //MATERIAL
    
    // We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "Model");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &toWorld[0][0]);
    
    glBindVertexArray(bbVAO);
    glEnable(GL_LINE_SMOOTH);
    glPointSize(15.0f); //for drawing points
    //    glLineWidth(500);
    GLfloat lineWidthRange[2];
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    glLineWidth(lineWidthRange[1]);
    
    glDrawArrays(GL_LINE_STRIP, 0, (GLuint)bigBuf.size());
    
    glBindVertexArray(0);
}

void boundingBox::update(float incMinX, float incMaxX,
                         float incMinY, float incMaxY,
                         float incMinZ, float incMaxZ)
{
    minX = incMinX;
    minY = incMinY;
    minZ = incMinZ;
    maxX = incMaxX;
    maxY = incMaxY;
    maxZ = incMaxZ;
}
void boundingBox::genBigBuf()
{
    //  (minX, minY, minZ)
    //  (minX, minY, minZ)
    
//          p7(x,Y,Z) _______________  p6(X,Y,Z)
//                   /|             /|
//                  / |            / |
//                 /  |           /  |
//                /   |  p2      /   |            ^ y
//               /    |  (X,Y,z)/    |            |
//    p3(x,Y,z) /_____|________/     |            |
//              |     |________|_____| (X,y,Z)    |       x
//              |     /(x,y,Z) |     /    p5      |------->
//              |    /  p4     |    /            /
//              |   /          |   /            /
//              |  /           |  /           |/_
//              | /            | /               -z
//              |/_____________|/
//        p0(x,y,z)            p1(X,y,z)
    
    
    //p0 -> p1
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
    
    //p1->p2
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);
    
    //p2->p3
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);

    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);
    
    //p3->p0
    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
//////
    //p4 -> p5
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
    
    //p5->p6
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
    
    //p6->p7
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
    
    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
    
    //p7->p4
    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
    
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
//////
    //p0 ->p4
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(minX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
    
    //p1->p5
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(minY);
    bigBuf.push_back(maxZ);
    
    //p2->p6
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(maxX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
    
    //p3->p7
    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(minZ);
    
    bigBuf.push_back(minX);
    bigBuf.push_back(maxY);
    bigBuf.push_back(maxZ);
}

void boundingBox::mtranslate(glm::vec3 tv){
    toWorld = glm::translate(glm::mat4(1.0f), tv) * toWorld;
}

void boundingBox::scale(glm::vec3 sv){
    toWorld = glm::scale(toWorld, sv);
}