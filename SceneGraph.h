//
//  SceneGraph.h
//  167Proj3
//
//  Created by adboom on 4/29/16.
//  Copyright © 2016 adboom. All rights reserved.
//

#ifndef SceneGraph_h
#define SceneGraph_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <string.h>
#include "OBJObject.h"

class Node{
public:
    virtual void draw(glm::mat4 C) = 0;
    virtual void update(glm::mat4 U) = 0;

};

class Group: public Node{
public:
    Group();
    std::list<Node*> nodes;
    glm::mat4 U = glm::mat4(1.0f);
    void addChild(Node*);
    void addChildren(std::vector<Node*>);
    void removeChild();
    void draw(glm::mat4);
    void update(glm::mat4);
};

class Geode: public Node{
public:
    virtual void update(glm::mat4) = 0;
    virtual void draw(glm::mat4) = 0;
    glm::mat4 M = glm::mat4(1.0f);
    };

class Camera: public Node{
public:
    Camera();
    glm::mat4 M;
    virtual void draw(glm::mat4 C);
    virtual void update(glm::mat4 U);
};

class MatrixTransform: public Group{
public:
    glm::mat4 M;
    MatrixTransform(glm::mat4);
    MatrixTransform();
    void draw(glm::mat4);
    void setUpdate(glm::mat4);
    void update(glm::mat4);
};

class Pod: public Geode{
public:
    Pod();
    OBJObject * p;
    void draw(glm::mat4);
    void update(glm::mat4);
    };

class Patch: public Geode {
public:
    GLuint VAO, VBO;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> cps;
    std::vector<GLfloat> bigBuf;
    GLint patchShade;
    glm::mat4 Gx, Gy, Gz, B;
    Patch(std::vector<glm::vec4>);
    glm::vec4 getPoint(float, glm::vec4, glm::vec4, glm::vec4, glm::vec4);
    void makeCurves();
    void setControl();
    void draw(glm::mat4);
    void update(glm::mat4);
    void update();
    void genBigBuf();
    void setIds(int, int, int, int);
};

class Point: public Geode {
public:
    int id;
    GLuint VAO, VBO;
    GLint selShade;
    GLint pointShade;
    glm::vec4 pos;
    bool selDraw;
    
    Point(glm::vec4, int);
    void draw(glm::mat4);
    void draw(glm::mat4, int);
    void update(glm::mat4);
    void moveTo(glm::vec4);
    void move(glm::vec4);
    void waitMove(glm::vec4);
};



#endif /* SceneGraph_h */
