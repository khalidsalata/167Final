#include "window.h"
#include "Cube.h"
#include "OBJObject.h"
#include "SceneGraph.h"

#define thisIsKhalid 0

const char* window_title = "GLFW Starter Project";
bool Window::khalid;
Cube* skyCube;
glm::vec3 tv;
glm::vec3 lastP, rockMove;
glm::vec3 yunit = glm::vec3(0.0f,1.0f,0.0f);
glm::mat4 armU;
glm::mat4 fU;
float vel, t;
bool camMode, click, manip, seeShadow, seeDepth, excessive, boxSee;
bool aHit;
int selected = 0;
float podPos, gypos, gxpos, initH;
float g = -0.0001f;
float yvel;
Pod* rock;
GLuint depthMapFBO, waterRefFBO;
GLuint waterRefMap;

std::vector<glm::vec3> ripples;
std::vector<glm::vec4> hitSpot;
std::vector<Drops> particles;

Camera *cam;
Point *c11, *c12, *c21, *c22, *c31, *c32, *c41, *c42, *c51, *c52, *c61, *c62, *c71, *c72, *c81, *c82;
Point *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
Patch *p0;
GLuint pVAO, pVBO, uniVAO, uniVBO, uniEBO;

std::vector<GLfloat> bigBuf;
std::vector<Point*> Window::ctPoints;
std::vector<glm::vec4> patchPoints;

GLint shaderProgram, depthProgram;
GLint pointShade, selShade, patchShade, shadowShade, rockShade, debugShade, dropShade, boxShade;
GLuint shadowBuffer = 0;
GLuint textureID, matrixID, depthBiasID, shadowMapID, depthMatrixID;
GLuint depthTexture, waterRefTexture, debugTexture;

std::vector<GLfloat> uniBuf;
std::vector<GLuint> uniIndex;


// Default camera parameters
glm::vec3 cam_pos(0.0f, 10.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

//Light location
glm::vec3 dirLightPos(0.0f, 15.0f, 5.0f);

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
glm::mat4 squareP;

void Window::initialize_objects()
{
<<<<<<< HEAD
    //Shaders
    shaderProgram = LoadShaders("/Users/adboom/Desktop/167Proj4/167Proj4/shader.vert", "/Users/adboom/Desktop/167Proj4/167Proj4/shader.frag");
    depthProgram = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/buffShade.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/buffShade.frag");
    patchShade = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/objShader.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/objShader.frag");
    selShade = LoadShaders("/Users/adboom/Desktop/167Proj4/167Proj4/selection.vert", "/Users/adboom/Desktop/167Proj4/167Proj4/selection.frag");
    pointShade = LoadShaders("/Users/adboom/Desktop/167Proj4/167Proj4/pointShader.vert", "/Users/adboom/Desktop/167Proj4/167Proj4/pointShader.frag");
    shadowShade = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/shadowShade.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/shadowShade.frag");
    rockShade = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/rockShader.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/rockShader.frag");
    debugShade = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/debugDepth.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/debugDepth.frag");
    dropShade = LoadShaders("/Users/adboom/Desktop/167Final/167Final/167Final/particleShade.vert", "/Users/adboom/Desktop/167Final/167Final/167Final/particleShade.frag");
    boxShade = LoadShaders("/Users/adboom/Downloads/bbShader.vert", "/Users/adboom/Downloads/bbShader.frag");
    
=======
    khalid = thisIsKhalid;
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
    //Native Objects
    skyCube = new Cube();
    skyCube->toWorld = glm::scale(skyCube->toWorld, glm::vec3(500.0f, 500.0f, 500.0f));
    rock = new Pod();
    camMode = true;
    click = manip = seeShadow = seeDepth = excessive = boxSee = false;
    boxSee = false;
    t = 0.0f;
        
    //Points without friends
    c1 = new Point(glm::vec4(-10.0f, 1.0f, -10.0f, 0.0f), 0, &pointShade, &selShade);
    c11 = new Point(glm::vec4(-10.0f + (20.0f/3.0f), 1.0f, -10.0f, 1.0f), 1, &pointShade, &selShade);
    c12 = new Point(glm::vec4(10.0f - (20.0f/3.0f), 1.0f, -10.0f, 1.0f), 2, &pointShade, &selShade);
    c2 = new Point(glm::vec4(10.07f, 1.0f, -10.0f, 0.0f), 3, &pointShade, &selShade);
    c21 = new Point(glm::vec4(-10.0f, 1.0f, -10.0f + (20.0f/3.0f), 1.0f), 4, &pointShade, &selShade);
    c22 = new Point(glm::vec4(-10.0f + (20.0f/3.0f), 1.0f, -10.0f + (20.0f/3.0f), 1.0f), 5, &pointShade, &selShade);
    c3 = new Point(glm::vec4(10.0f - (20.0f/3.0f), 1.0f, -10.0f + (20.0f/3.0f), 1.0f), 6, &pointShade, &selShade);
    c31 = new Point(glm::vec4(10.0f, 1.0f, -10.0f + (20.0f/3.0f), 1.0f), 7, &pointShade, &selShade);
    c32 = new Point(glm::vec4(-10.0f, 1.0f, 10.0f - (20.0f/3.0f), 1.0f), 8, &pointShade, &selShade);
    c4 = new Point(glm::vec4(-10.0f + (20.0f/3.0f), 1.0f, 10.0f - (20.0f/3.0f), 1.0f), 9, &pointShade, &selShade);
    c41 = new Point(glm::vec4(10.0f - (20.0f/3.0f), 1.0f, 10.0f - (20.0f/3.0f), 1.0f), 10, &pointShade, &selShade);
    c42 = new Point(glm::vec4(10.0f, 1.0f, 10.0f - (20.0f/3.0f), 1.0f), 11, &pointShade, &selShade);
    c5 = new Point(glm::vec4(-10.0f, 1.0f, 10.0f, 0.0f), 12, &pointShade, &selShade);
    c51 = new Point(glm::vec4(-10.0f + (20.0f/3.0f), 1.0f, 10.0f, 1.0f), 13, &pointShade, &selShade);
    c52 = new Point(glm::vec4(10.0f - (20.0f/3.0f), 1.0f, 10.0f, 1.0f), 14, &pointShade, &selShade);
    c6 = new Point(glm::vec4(10.07f, 1.0f, 10.0f, 0.0f), 15, &pointShade, &selShade);
    
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
    
    //populate patch control vector
    for(int i = 0; i < 16; i++){
        patchPoints.push_back(ctPoints[i]->pos);
    }
    
    //Let's get a patch
    p0 = new Patch(patchPoints);
    
    //Flatten the rock
    rock->p->scale(glm::vec3(1.0f, 0.5f, 1.0f));
    //Move it up
    rock->p->mtranslate(glm::vec3(5.0f, 2.5f, 5.0f));
    
    tv = lastP = glm::vec3(0.0f,0.0f,0.0f);

    //Texture for water scene reflection
    glGenTextures(1, &waterRefTexture);
    glBindTexture(GL_TEXTURE_2D, waterRefTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
<<<<<<< HEAD
    //Buffer to do our water ref snapshot
    glGenFramebuffers(1, &waterRefFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, waterRefFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, waterRefTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    //Set square perspective
    squareP = glm::perspective(180.0f, 1.0f, 0.1f, 1000.0f);
    
    hitSpot.push_back(glm::vec4(0.0f, 0.99f, 0.0f, 1.0f));
    
    yvel = -0.01f;
    
    rockMove = glm::normalize(glm::vec3(-10.0f, 0.0f, -10.0f));
    rockMove *= 0.05f;
=======
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
    shaderProgram = LoadShaders("../shader.vert", "../shader.frag");
#else // Not windows
    if(khalid){
    shaderProgram = LoadShaders("/Users/adboom/Downloads/skybox/shader.vert", "/Users/adboom/Downloads/skybox/shader.frag");
    } else {
    shaderProgram = LoadShaders("/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/shader.vert", "/Users/ahmed.elhosseiny/Documents/_CSE 167/Elhosseiny-Ahmed/CSE-167-Final/CSE-167-Final/167Final/shader.frag");
    }
#endif
>>>>>>> 1403a6471abeb90326555cf1b1d4d9b5c2e33959
}

void Window::clean_up()
{
    glDeleteProgram(shaderProgram);
    glDeleteProgram(depthProgram);
    glDeleteProgram(patchShade);
    glDeleteProgram(selShade);
    glDeleteProgram(pointShade);
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
    t += 0.001f;
    
    for(int i = 0; i < ripples.size(); i++){
        if(ripples[i].z >= 2.0f){
            ripples.erase(ripples.begin() + i);
        }
        else{
            ripples[i].z += 0.01f;
            p0->makeRipples(ripples[i]);
        }
    }
    
    for(int i = 0; i < particles.size(); i++){
        int s = (int) particles[i].droplets.size();
        float y = particles[i].origin.y;
        if(particles[i].droplets[s - 1].y < y){
            particles.erase(particles.begin() + i);
        }
        else{
            particles[i].move();
        }
    }
    
    rockMove.y = yvel + (-2.0f) * pow(t, 2);
    
    if(rock->p->boundBox->checkCollisions(hitSpot) != true){
        rock->p->mtranslate(rockMove);
    }
    else{
        t = 0.0f;
        aHit = true;
        yvel = 0.01f;
        rockMove.y = yvel;
        rock->p->mtranslate(rockMove);
    }
     rock->p->selforbit(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Window::display_callback(GLFWwindow* window)
{
    //Redraw scene from perspective of water
    glBindFramebuffer(GL_FRAMEBUFFER, waterRefFBO);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    V = glm::lookAt(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glViewport(0, 0, 1024, 1024);
//    P = squareP;
    P = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    skyCube->draw(shaderProgram);
    rock->draw(rockShade);
    for(int i = 0; i < particles.size(); i++){
        particles[i].draw(dropShade);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
    glViewport(0, 0, width, height);
    
    //Use the shader of programID
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawEverything(0);
    
     
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
            cam_pos = glm::vec3(0.0f,30.0f,-1.0f);
            V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            lastP = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        else if(key == GLFW_KEY_C){
            camMode = !camMode;
        }
        else if(key == GLFW_KEY_T){
            ripples.clear();
        }
        else if(key == GLFW_KEY_M){
            manip = !manip;
        }
        else if (key == GLFW_KEY_S){
            seeShadow = !seeShadow;
        }
        else if (key == GLFW_KEY_A){
            seeDepth = !seeDepth;
        }
        else if (key == GLFW_KEY_L){
            cam_pos = dirLightPos;
            V = glm::lookAt(cam_pos, cam_look_at, cam_up);
        }
        else if (key == GLFW_KEY_E){
            excessive = !excessive;
        }
        else if (key == GLFW_KEY_B){
            boxSee = !boxSee;
        }
    }
}

void Window::mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glm::vec3 worldPlace = glm::vec3(0.0f);
    
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
        screenToWorld(xpos, ypos, &worldPlace);
        printf("world coords: %f, %f, %f\n", worldPlace.x, worldPlace.y, worldPlace.z);
        if(std::abs(worldPlace.x) < 10.0f && std::abs(worldPlace.z) < 10.0f){
            if(seeDepth){
                ripples.push_back(glm::vec3(worldPlace.x, worldPlace.z, 0.0f));
                Drops d = Drops(worldPlace, excessive);
                particles.push_back(d);
            }
            else{
            rock->p->hardTranslate(glm::vec3(worldPlace.x, 1.5f, worldPlace.z));
            }
        }
    }
    
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        selected = 101;
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
        if(selected < 25){ pointMove(ctPoints[selected], glm::vec4(tv, 1.0f)); }
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
//    float xpos = 2.0f * x;
//    float ypos = height - (2.0f * y);
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
    p0->cps[p->id] = p->pos;
    p0->update(false);
}

void Window::drawEverything(int mode){
    GLuint patchUsed, rockUsed;
    if(mode != 0){
        patchUsed = rockUsed = depthProgram;
    }
    else{
        if(seeShadow){ patchUsed = shadowShade; }
        else{ patchUsed = patchShade; }
        
        rockUsed = rockShade;
    }
    // Render the cube
    skyCube->draw(shaderProgram);
    
    GLuint scamID = glGetUniformLocation(patchUsed,"cameraPos");
    GLuint lightPosID = glGetUniformLocation(shadowShade, "lightPos");
    glUniform3fv(scamID, 1, &cam_pos[0]);
    glUniform3fv(lightPosID, 1, &dirLightPos[0]);
    rock->draw(rockUsed);
    
    if(manip){
        pDraw();
    }
    
    float ax = rock->p->boundBox->getMaxX() + rock->p->boundBox->getMinX();
    ax = ax/2.0f;
    float az = rock->p->boundBox->getMaxZ() + rock->p->boundBox->getMinZ();
        az = az/2.0f;
    if(abs(ax) >= 10.0f || abs(az) >= 10.0f){
        rock->p->hardTranslate(glm::vec3(9.9f, 2.5f, 9.9f));
        yvel = -0.01f;
        aHit = false;
    }

    if(aHit){
        if(boxSee) {
        rock->p->boundBox->draw(boxShade);
        }
        ripples.push_back(glm::vec3(ax, az, 0.0f));
        Drops d = Drops(glm::vec3(ax, 1.0f, az), excessive);
        particles.push_back(d);
        aHit = false;
    }
    
    //Draw the water surface
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, waterRefTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyCube->textureID);
    p0->draw(patchUsed);
    
    for(int i = 0; i < particles.size(); i++){
        particles[i].draw(dropShade);
    }
}

void Window::screenToWorld(float xpos, float ypos, glm::vec3* result){
    //Store viewport
    GLfloat vp[4];
    glm::vec4 viewport = glm::vec4(0.0f);
    glGetFloatv(GL_VIEWPORT, vp);
    viewport = glm::vec4(vp[0], vp[1], vp[2], vp[3]);

    //Adjust mouse position for usage
    xpos = 2.0f * xpos;
    ypos = height - (2.0f * ypos);
    
    //Obtain z coordinate
    GLfloat zpos;
    glReadPixels(xpos, ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zpos);
    
    //Our total location in screen space
    glm::vec3 screen = glm::vec3(xpos, ypos, zpos);
    
    //Call unproject
    *result = glm::unProject(screen, V, P, viewport);
   }

