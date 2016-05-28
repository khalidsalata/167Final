#include "window.h"
#include "Cube.h"
#include "OBJObject.h"
#include "SceneGraph.h"

const char* window_title = "GLFW Starter Project";
Cube* skyCube;
glm::vec3 tv;
glm::vec3 lastP;
glm::vec3 yunit = glm::vec3(0.0f,1.0f,0.0f);
glm::mat4 armU;
glm::mat4 fU;
float vel;
bool camMode, click, run;
int selected = 0;
float podPos, gypos, gxpos, initH;
float g = -0.0001f;

Camera *cam;
Point *c11, *c12, *c21, *c22, *c31, *c32, *c41, *c42, *c51, *c52, *c61, *c62, *c71, *c72, *c81, *c82;
Point *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
Patch *p0;
GLuint pVAO, pVBO;

std::vector<GLfloat> bigBuf;
std::vector<Point*> Window::ctPoints;
std::vector<glm::vec4> patchPoints;

GLint shaderProgram;
GLint pointShade;

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, -20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
    //Native Objects
    skyCube = new Cube();
    
    camMode = true;
    click = false;
    
    //Points without friends
    c1 = new Point(glm::vec4(-10.0f, 10.0f, -10.0f, 0.0f), 0);
    c11 = new Point(glm::vec4(-5.0f, 0.0f, -10.0f, 1.0f), 1);
    c12 = new Point(glm::vec4(5.0f, 0.0f, -10.0f, 1.0f), 2);
    c2 = new Point(glm::vec4(10.07f, 5.0f, -10.0f, 0.0f), 3);
    c21 = new Point(glm::vec4(-10.0f, 0.0f, -5.0f, 1.0f), 4);
    c22 = new Point(glm::vec4(-5.0f, 0.0f, -5.0f, 1.0f), 5);
    c3 = new Point(glm::vec4(5.0f, 0.0f, -5.0f, 0.0f), 6);
    c31 = new Point(glm::vec4(10.0f, 0.0f, -5.0f, 1.0f), 7);
    c32 = new Point(glm::vec4(-10.0f, 0.0f, 5.0f, 1.0f), 8);
    c4 = new Point(glm::vec4(-5.07f, 0.0f, 5.0f, 0.0f), 9);
    c41 = new Point(glm::vec4(5.0f, 0.0f, 5.0f, 1.0f), 10);
    c42 = new Point(glm::vec4(10.0f, 0.0f, 5.0f, 1.0f), 11);
    c5 = new Point(glm::vec4(-10.0f, 5.0f, 10.0f, 0.0f), 12);
    c51 = new Point(glm::vec4(-5.0f, 0.0f, 10.0f, 1.0f), 13);
    c52 = new Point(glm::vec4(5.0f, 0.0f, 10.0f, 1.0f), 14);
    c6 = new Point(glm::vec4(10.07f, -10.0f, 10.0f, 0.0f), 15);
    
    
    //Into the point vector
    ctPoints.push_back(c1);
    ctPoints.push_back(c11);
    ctPoints.push_back(c12);
    ctPoints.push_back(c2);
    ctPoints.push_back(c21);
    ctPoints.push_back(c22);
    ctPoints.push_back(c3);
    ctPoints.push_back(c31);
    ctPoints.push_back(c32);
    ctPoints.push_back(c4);
    ctPoints.push_back(c41);
    ctPoints.push_back(c42);
    ctPoints.push_back(c5);
    ctPoints.push_back(c51);
    ctPoints.push_back(c52);
    ctPoints.push_back(c6);
    
    //Enforce C1
    //forceContinuity();
    
    //populate patch control vector
    for(int i = 0; i < 16; i++){
        patchPoints.push_back(ctPoints[i]->pos);
    }
    
    //Let's get a patch
    p0 = new Patch(patchPoints);
    
    tv = lastP = glm::vec3(0.0f,0.0f,0.0f);
    
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
    shaderProgram = LoadShaders("../shader.vert", "../shader.frag");
#else // Not windows
    shaderProgram = LoadShaders("/Users/adboom/Desktop/167Proj4/167Proj4/shader.vert", "/Users/adboom/Desktop/167Proj4/167Proj4/shader.frag");
#endif
}

void Window::clean_up()
{
    glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    
    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create the GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
    
    // Check if the window could not be created
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }
    
    // Make the context of the window
    glfwMakeContextCurrent(window);
    
    // Set swap interval to 1
    glfwSwapInterval(1);
    
    // Get the width and height of the framebuffer to properly resize the window
    glfwGetFramebufferSize(window, &width, &height);
    // Call the resize callback to make sure things get drawn immediately
    Window::resize_callback(window, width, height);
    
    return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
    Window::width = width;
    Window::height = height;
    // Set the viewport size
    glViewport(0, 0, width, height);
    
    if (height > 0)
    {
        P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}

void Window::idle_callback()
{
    
}

void Window::display_callback(GLFWwindow* window)
{
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use the shader of programID
    glUseProgram(shaderProgram);
    
    // Render the cube

    skyCube->draw(shaderProgram);

    p0->draw(glm::mat4(1.0f));
    pDraw();
    
    // Gets events, including input such as keyboard and mouse or window resizing
    glfwPollEvents();
    // Swap buffers
    if(click == false){
        glfwSwapBuffers(window);
    }
    else{ click = false; }
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if(key == GLFW_KEY_R){
            cam_pos = glm::vec3(0.0f,0.0f,-20.0f);
            V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            lastP = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        else if(key == GLFW_KEY_C){
            camMode = !camMode;
        }
        else if(key == GLFW_KEY_T){
            
        }
        else if(key == GLFW_KEY_G){
            run = !run;
        }
    }
}

void Window::mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && camMode){
        trackBallMapping((float) xpos, (float) ypos, &lastP);
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !camMode){
        click = true;
        pDraw();
        unsigned char pix[4];
        
        glReadPixels(2.0f * xpos, height - (2.0f * ypos), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);
        
        unsigned int p = pix[0];
        if(p < 25){ selected = p; };
        gypos = ypos;
        gxpos = xpos;
    }
    
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        selected = 100;
    }
}

void Window::mousePos_callback(GLFWwindow* window, double xpos, double ypos)
{
    double deltax = gxpos - xpos;
    double deltay = gypos - ypos;
    glm::vec4 easy;
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) ==  GLFW_PRESS && camMode){
        trackBallMapping((float) xpos, (float) ypos, &tv);
        vel = glm::length(tv - lastP);
        glm::vec3 temp = glm::cross(lastP, tv);
        lastP = tv;
        tv = temp;
        easy = glm::rotate(glm::mat4(1.0f), vel * glm::pi<float>(), tv) * glm::vec4(cam_pos, 1.0f);
        if(isnan(easy.x)){
            easy = glm::rotate(glm::mat4(1.0f), vel * glm::pi<float>(), lastP) * glm::vec4(cam_pos, 1.0f);
        }
        else{ cam_pos = glm::vec3(easy.x, easy.y, easy.z); }
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
        }
    else if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) ==  GLFW_PRESS && !camMode){
        
        glm::vec3 e = cam_pos;
        glm::vec3 d = cam_look_at;
        
        glm::vec3 z = glm::normalize(e - d);
        glm::vec3 x = glm::normalize(glm::cross(z, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 y = glm::normalize(glm::cross(x, z));
        
        tv = ((float) deltax/40.0f * x) + ((float) deltay/40.0f * y);
        
        if(isnan(tv.x)){
            tv = lastP;
        }
        if(selected < 25){
            //printf("Moving %d\n", selected);
            //If it's a blue point change it's adjacents
            if(ctPoints[selected]->id % 3 == 0){
                if(selected == 0){
                    ctPoints[23]->waitMove(glm::vec4(tv, 1.0f));
                    ctPoints[1]->waitMove(glm::vec4(tv, 1.0f));
                }
                else if(selected == 23){
                    ctPoints[0]->waitMove(glm::vec4(tv, 1.0f));
                    ctPoints[22]->waitMove(glm::vec4(tv, 1.0f));
                }
                else{
                    ctPoints[selected + 1]->waitMove(glm::vec4(tv, 1.0f));
                    ctPoints[selected - 1]->waitMove(glm::vec4(tv, 1.0f));
                }
                pointMove(ctPoints[selected], glm::vec4(tv, 1.0f));
            }
            //If it's a green point just the point itself and its partner
            else{
                //printf("Id cps[0] = %d\n", temp->c->cps[0]);
                pointMove(ctPoints[selected], glm::vec4(tv, 1.0f));
            }
        }
        gypos = ypos;
        gxpos = xpos;
    }
}

void Window::mouseScroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    glm::vec3 dir = glm::normalize(cam_pos);
    if(yoffset > 0){ cam_pos = cam_pos + dir; }
    else if(yoffset < 0){
        if(cam_pos - dir != glm::vec3(0.0f)){
            cam_pos = cam_pos - dir;
        }
    }
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
}

void Window::trackBallMapping(float x, float y, glm::vec3 *toSet){
    float xpos = (4.0*x - width) / width;
    float ypos = (height - 4.0*y) / height;
    float d = glm::length(glm::vec3(xpos,ypos,0));
    d = (d<1.0) ? d : 1.0;
    *toSet = glm::normalize(glm::vec3(xpos,ypos,sqrtf(1.001 - d*d)));
}

void Window::forceContinuity(){
    //Neighboring Control points
    c11->moveTo(c1->pos + (c1->pos - c82->pos));
    c21->moveTo(c2->pos + (c2->pos - c12->pos));
    c31->moveTo(c3->pos + (c3->pos - c22->pos));
    c41->moveTo(c4->pos + (c4->pos - c32->pos));
    c51->moveTo(c5->pos + (c5->pos - c42->pos));
    c61->moveTo(c6->pos + (c6->pos - c52->pos));
    c71->moveTo(c7->pos + (c7->pos - c62->pos));
    c81->moveTo(c8->pos + (c8->pos - c72->pos));
}

void Window::pDraw(){
    int m = 0;
    if(click){ m = 1; }
    for(int i = 0; i < ctPoints.size(); i++){
        ctPoints[i]->draw(glm::mat4(1.0f), m);
    }
}


void Window::pointMove(Point* p, glm::vec4 toPoint){
    
    //toPoint = glm::vec4(newx, newy, newz, 0.0f);
    
    p->pos = p->pos + toPoint;
    p->M = glm::translate(glm::mat4(1.0f), glm::vec3(toPoint)) * p->M;

}