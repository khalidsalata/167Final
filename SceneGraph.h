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

class Pod {
public:
    Pod();
    OBJObject * p;
    GLint* shade;
    void draw(GLuint);
    void update(glm::mat4);
    };

class Patch {
public:
    GLuint VAO, VBO, EBO;
    std::vector< std::vector<glm::vec3> > vertices;
    std::vector< std::vector<glm::vec3> > normals;
    std::vector< std::vector<glm::vec3> > preVert;
    std::vector<GLuint> indicies;
    std::vector<glm::vec4> cps;
    std::vector<GLfloat> bigBuf;
    GLint* patchShade;
    GLint depthTexture;
    glm::mat4 Gx, Gy, Gz, B;
    Patch(std::vector<glm::vec4>);
    glm::vec4 getPoint(float, glm::vec4, glm::vec4, glm::vec4, glm::vec4);
    bool up;
    void makeCurves();
    void setControl();
    void draw(GLuint);
    void update(glm::mat4);
    void update(bool);
    void genBigBuf();
    void makeIndicies();
    void makeRipples(glm::vec3);
    void splash(glm::vec3);
    void hitNeighbors(int, int , int, float);
};

class Point {
public:
    int id;
    GLuint VAO, VBO;
    GLint* selShade;
    GLint* pointShade;
    glm::vec4 pos;
    bool selDraw;
    glm::mat4 M = glm::mat4(1.0f);
    
    Point(glm::vec4, int, GLint*, GLint*);
    void draw(glm::mat4);
    void draw(glm::mat4, int);
    void update(glm::mat4);
    void moveTo(glm::vec4);
    void move(glm::vec4);
    void waitMove(glm::vec4);
};

class Drops{
public:
    GLuint VAO, VBO, EBO;
    glm::vec3 origin;
    float time;
    GLint* selShade;
    std::vector<glm::vec3> droplets;
    std::vector<glm::vec3> vels;
    std::vector<GLfloat> bigBuf;
    Drops(glm::vec3, bool);
    void genBigBuf();
    void move();
    void draw(GLint);
    void update();
    
};


#endif /* SceneGraph_h */
