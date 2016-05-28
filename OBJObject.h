#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>
#include <cfloat>

class OBJObject
{
    
public:
    OBJObject(const char* filepath);
    ~OBJObject();
    
    GLuint VBO, VAO, EBO;
    const char* name;
    float expo;
    void parse(const char* filepath);
    static std::map<const char*, std::vector< std::vector<glm::vec3> > > perstV;
    static std::map<const char*, std::vector<GLuint> > perstIn;
    static std::map<const char*, int> perstCount;
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indices;
    std::vector<glm::vec3> normals;
    std::vector<GLfloat> bigBuf;
    glm::mat4 toWorld;
    glm::mat4 tempW;
    float angle;
    GLint objShade;
    int facecount;
    void draw(glm::mat4, int);
    void update(int);
    void update(glm::vec3);
    void update(glm::vec3, float deg);
    void spin(float);
    void translate(int);
    void mtranslate(glm::vec3);
    void scale(glm::vec3);
    void scale(int);
    void orbit(int);
    void selforbit(float, glm::vec3);
    void morbit(glm::vec3, float);
    void genBigBuf();
    void setExpo(float);
};

#endif