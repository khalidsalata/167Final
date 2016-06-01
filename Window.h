#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "OBJObject.h"
#include "SceneGraph.h"

class Window
{
public:
    static bool khalid;
    static int width;
    static int height;
    static glm::mat4 P;
    static glm::mat4 V;
    static std::vector<Point*> ctPoints;
    static void initialize_objects();
    static void clean_up();
    static GLFWwindow* create_window(int width, int height);
    static void resize_callback(GLFWwindow* window, int width, int height);
    static void idle_callback();
    static void display_callback(GLFWwindow*);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mousePos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void trackBallMapping(float, float, glm::vec3*);
    static void pDraw();
    static void forceContinuity();
    static void ride();
    static void drawPod();
    static void pointMove(Point*, glm::vec4 toPoint);
};

#endif
