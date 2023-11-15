//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//MY project

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "stb_image.h"
#include "movingobject.h"
#include <iostream>
#include "sphere.h"
#include "flyer.h"
#include "sylinder.h"
#include "Sphere2.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x,float y,float z);
void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void building(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x ,float z);
void mall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float z);
void road(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void tree(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void pool(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x,float y,float z);
void trafficlight(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void trafficlight2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void roof2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void roof3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z);
void func(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z,float g);
void func2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float g);
void sun(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void clock1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void clock2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float r = 0.5f;
float angle_t = 0.5f;
bool fan_on = false;
float speed = 0.5f;
bool boatF = false;
float boat_ang = 20.0f;
float inc = 0.01;
float inc2 = 0.01;
float truck_z = -10.0;
float truck_angle = 0.0;
int cnt = 0;
float clock_z = 0.0;
float deg = 0.001;
float clock_y = 0.0;
float deg2 = 0.001 / 18.0;
float truck_x = 0.0;

// camera
Camera camera(glm::vec3(0.0f, 1.1f, 5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(1.50f,  1.50f,  0.0f),
    glm::vec3(-1.5f,  1.5f,  0.0f),
    glm::vec3(1.0f,  4.5f,  0.5f),
    //glm::vec3(-1.5f,  -1.5f,  0.0f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);


PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);


PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);


// light settings
bool onOffPointToggle = true;
bool onOffSpotToggle = true;
bool onOffDirectToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    float FLYER_Y = 0;
    bool  FLYER_Y_INCREASE = true;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    string diffuseMapPath = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/water4.bmp";
    string specularMapPath = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/water4.bmp";

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath1 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building1.bmp";
    string specularMapPath1 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building1.bmp";

    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube1 = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath2 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building10.bmp";
    string specularMapPath2 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building10.bmp";

    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath3 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building3.bmp";
    string specularMapPath3 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building3.bmp";

    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath4 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building4.bmp";
    string specularMapPath4 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building4.bmp";

    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube4 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath5 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building5.bmp";
    string specularMapPath5 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building5.bmp";

    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube5 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath6 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building6.bmp";
    string specularMapPath6 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building6.bmp";

    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube6 = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath7 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building7.bmp";
    string specularMapPath7 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building7.bmp";

    unsigned int diffMap7 = loadTexture(diffuseMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube7 = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath8 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building8.bmp";
    string specularMapPath8 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building8.bmp";

    unsigned int diffMap8 = loadTexture(diffuseMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube8 = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath9 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building9.bmp";
    string specularMapPath9 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/building9.bmp";

    unsigned int diffMap9 = loadTexture(diffuseMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube9 = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath10 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop1.bmp";
    string specularMapPath10 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop7.bmp";

    unsigned int diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube10 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath11 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop1.bmp";
    string specularMapPath11 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop7.bmp";

    unsigned int diffMap11 = loadTexture(diffuseMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube11 = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath12 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop1.bmp";
    string specularMapPath12 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop1.bmp";

    unsigned int diffMap12 = loadTexture(diffuseMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube12 = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath13 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop6.bmp";
    string specularMapPath13 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/shop6.bmp";

    unsigned int diffMap13 = loadTexture(diffuseMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube13 = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath14 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/signboard7.bmp";
    string specularMapPath14 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/tree1.bmp";

    unsigned int diffMap14 = loadTexture(diffuseMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube14 = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath15 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/road4.bmp";
    string specularMapPath15 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/tree1.bmp";

    unsigned int diffMap15 = loadTexture(diffuseMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube15 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath16 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/road.bmp";
    string specularMapPath16 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/tree1.bmp";

    unsigned int diffMap16 = loadTexture(diffuseMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube16 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath17 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/watch1.bmp";
    string specularMapPath17 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/watch1.bmp";

    unsigned int diffMap17 = loadTexture(diffuseMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube17 = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath18 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";
    string specularMapPath18 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";

    unsigned int diffMap18 = loadTexture(diffuseMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap18 = loadTexture(specularMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube18 = Cube(diffMap18, specMap18, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath19 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/floor3.bmp";
    string specularMapPath19 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";

    unsigned int diffMap19 = loadTexture(diffuseMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap19 = loadTexture(specularMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube19 = Cube(diffMap19, specMap19, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath20 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/football1.bmp";
    string specularMapPath20 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";

    unsigned int diffMap20 = loadTexture(diffuseMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap20 = loadTexture(specularMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube20 = Cube(diffMap20, specMap20, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath22 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/floor4.PNG";
    string specularMapPath22 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";

    unsigned int diffMap22 = loadTexture(diffuseMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap22 = loadTexture(specularMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube22 = Cube(diffMap22, specMap22, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath23 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/floor4.PNG";
    string specularMapPath23 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/grass.bmp";

    unsigned int diffMap23 = loadTexture(diffuseMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap23 = loadTexture(specularMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube23 = Cube(diffMap23, specMap23, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath24 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/traffic2.bmp";
    string specularMapPath24 = "D:/graphics/3D-City-Architecture-Design-OpenGL-CPP/images/sky1.PNG";

    unsigned int diffMap24 = loadTexture(diffuseMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap24 = loadTexture(specularMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube24 = Cube(diffMap24, specMap24, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);



    


    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
    
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    float ver_arr[] = {

   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
   0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f,
   0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f,
   -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f,
   -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f,
   -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f,
   -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f,
   -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f,
   0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f,
   0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f,

   1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
   0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f,
   0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f,
   -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f,
   -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f,
   -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f,
   -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f,
   -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f,
   0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f,
   0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f,


   1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
   0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f,
   0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f,
   -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f,
   -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f,
   -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f,
   -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f,
   -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f,
   0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f,
   0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f,

   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
   0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f,
   0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f,
   -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f,
   -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f,
   -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f,
   -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f,
   -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f,
   0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f,
   0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f,


   0.0,-1.0,0.0, 0.0,-1.0,0.0,
   0.0,1.0,0.0, 0.0,1.0,0.0

    };
    unsigned int ind_arr[] = {
        0, 11, 1,
        11, 0, 10,
        1, 12, 2,
        12, 1, 11,
        2, 13, 3,
        13, 2, 12,
        3, 14, 4,
        14, 3, 13,
        4, 15, 5,
        15, 4, 14,
        5, 16, 6,
        16, 5, 15,
        6, 17, 7,
        17, 6, 16,
        7, 18, 8,
        18, 7, 17,
        8, 19, 9,
        19, 8, 18,
        9, 10, 0,
        10, 9, 19,

        40,20,21,
        40,21,22,
        40,22,23,
        40,23,24,
        40,24,25,
        40,25,26,
        40,26,27,
        40,27,28,
        40,28,29,
        40,29,20,

        41,30,31,
        41,31,32,
        41,32,33,
        41,33,34,
        41,34,35,
        41,35,36,
        41,36,37,
        41,37,38,
        41,38,39,
        41,39,30


        /*
        21,10,11,
        21,11,12,
        21,12,13,
        21,13,14,
        21,14,15,
        21,15,16,
        21,16,17,
        21,17,18,
        21,18,19,
        21,19,10*/

    };

    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    unsigned int cVAO, cVBO, cEBO;
    glGenVertexArrays(1, &cVAO);
    glGenBuffers(1, &cVBO);
    glGenBuffers(1, &cEBO);

    glBindVertexArray(cVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver_arr), ver_arr, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind_arr), ind_arr, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //end of cylingder

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.518f, 0.71f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
       // pointlight4.setUpPointLight(lightingShader);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        bed(cubeVAO, lightingShader, model,0,0,12);
        bed(cubeVAO, lightingShader, model, 0,0,24);
        floor(cubeVAO, lightingShader, model);
       // road(cubeVAO, lightingShader, model);
        //building(cubeVAO, lightingShader, model,1,0);
        //building(cubeVAO, lightingShader, model,1,-4.0);
        //building(cubeVAO, lightingShader, model,1, -2.0);
        //building(cubeVAO, lightingShader, model, 3, 0);
        //building(cubeVAO, lightingShader, model, 3, -4.0);
        //building(cubeVAO, lightingShader, model, 3, -2.0);
        //tree(cubeVAO, lightingShader, model);
        pool(cubeVAO, lightingShader, model,0,0,18);
        trafficlight(cubeVAO, lightingShader, model, 10.5, 0, 0);
        trafficlight(cubeVAO, lightingShader, model, 24.5, 0, 12.0);
        trafficlight2(cubeVAO, lightingShader, model, 10.5, 0, 1.0);
        roof(cubeVAO, lightingShader, model,15,0,0);
        roof(cubeVAO, lightingShader, model, 15, 0, 4.0);
        roof(cubeVAO, lightingShader, model, 15, 0, 8.0);
        roof(cubeVAO, lightingShader, model, 5.0, 0, 0);
        roof(cubeVAO, lightingShader, model, 5.0, 0, 4.0);
        roof(cubeVAO, lightingShader, model, 5.0, 0, 8.0);
        roof(cubeVAO, lightingShader, model, 10.0, 0, 0);
        roof(cubeVAO, lightingShader, model, 10.0, 0, 4.0);
        roof(cubeVAO, lightingShader, model, 10.0, 0, 8.0);

        roof2(cubeVAO, lightingShader, model, 17, 0, 15.0);
        roof2(cubeVAO, lightingShader, model, 3, -0.1, 9.2);
        roof3(cubeVAO, lightingShader, model, 17, 0, 15.0);
        roof3(cubeVAO, lightingShader, model, 18, 0, 15.0);
        roof3(cubeVAO, lightingShader, model, 3, -0.1, 9.2);
        roof3(cubeVAO, lightingShader, model, 4.01, -0.1, 9.2);

        func(cubeVAO, lightingShader, model, 0,0,0,0.01);
        func2(cubeVAO, lightingShader, model, 0,0,0,0.01);
        sun(cubeVAO, lightingShader, model);
        clock1(cubeVAO, lightingShader, model);
        clock2(cubeVAO, lightingShader, model);


        roof(cubeVAO, lightingShader, model, -5.0, 0, 0.0);
        roof(cubeVAO, lightingShader, model, -5.0, 0, 4.0);
        roof(cubeVAO, lightingShader, model, -10.0, 0, 0.0);
        roof(cubeVAO, lightingShader, model, -10.0, 0, 4.0);
        //mall(cubeVAO, lightingShader, model, 3, -2.0);
        //mall(cubeVAO, lightingShader, model, 3, -4.0);



        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 3; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //Texture
        //texture
        glm::mat4 modelTexture = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 translate1 = glm::mat4(1.0f);
        glm::mat4 translate2 = glm::mat4(1.0f);
        glm::mat4 translate3 = glm::mat4(1.0f);
        glm::mat4 translate4 = glm::mat4(1.0f);
        glm::mat4 translate5 = glm::mat4(1.0f);
        glm::mat4 translate6 = glm::mat4(1.0f);
        glm::mat4 translate7 = glm::mat4(1.0f);
        glm::mat4 translate8 = glm::mat4(1.0f);
        glm::mat4 translate9 = glm::mat4(1.0f);
        glm::mat4 translate10 = glm::mat4(1.0f);
        glm::mat4 translate11 = glm::mat4(1.0f);
        glm::mat4 translate12 = glm::mat4(1.0f);
        glm::mat4 translate13 = glm::mat4(1.0f);
        glm::mat4 translate14 = glm::mat4(1.0f);
        glm::mat4 translate15 = glm::mat4(1.0f);
        glm::mat4 translate16 = glm::mat4(1.0f);
        glm::mat4 translate17 = glm::mat4(1.0f);
        glm::mat4 translate18 = glm::mat4(1.0f);
        glm::mat4 translate19 = glm::mat4(1.0f);
        glm::mat4 translate20 = glm::mat4(1.0f);
        glm::mat4 translate21 = glm::mat4(1.0f);
        glm::mat4 translate22 = glm::mat4(1.0f);
        glm::mat4 translate23 = glm::mat4(1.0f);
        glm::mat4 translate24 = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);
        glm::mat4 scale1 = glm::mat4(1.0f);
        glm::mat4 scale2 = glm::mat4(1.0f);
        glm::mat4 scale3 = glm::mat4(1.0f);
        glm::mat4 scale4 = glm::mat4(1.0f);
        glm::mat4 scale5 = glm::mat4(1.0f);
        glm::mat4 scale6 = glm::mat4(1.0f);
        glm::mat4 scale7 = glm::mat4(1.0f);
        glm::mat4 scale8 = glm::mat4(1.0f);
        glm::mat4 scale9 = glm::mat4(1.0f);
        glm::mat4 scale10 = glm::mat4(1.0f);
        glm::mat4 scale11 = glm::mat4(1.0f);
        glm::mat4 scale12 = glm::mat4(1.0f);
        glm::mat4 scale13 = glm::mat4(1.0f);
        glm::mat4 scale14 = glm::mat4(1.0f);
        glm::mat4 scale15 = glm::mat4(1.0f);
        glm::mat4 scale16 = glm::mat4(1.0f);
        glm::mat4 scale17 = glm::mat4(1.0f);
        glm::mat4 scale18 = glm::mat4(1.0f);
        glm::mat4 scale19 = glm::mat4(1.0f);
        glm::mat4 scale20 = glm::mat4(1.0f);
        glm::mat4 scale21 = glm::mat4(1.0f);
        glm::mat4 scale22 = glm::mat4(1.0f);
        glm::mat4 scale23 = glm::mat4(1.0f);
        glm::mat4 scale24 = glm::mat4(1.0f);

        glm::mat4 rotate1 = glm::mat4(1.0f);

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("view", view);
        lightingShaderWithTexture.setMat4("projection", projection);

        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);

        translate = glm::translate(identityMatrix, glm::vec3(-4.0, -0.25, 13.0));
        scale = glm::scale(identityMatrix, glm::vec3(6.0, 0.55, 10.0));
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * translate * scale);

        //building 1
        translate1 = glm::translate(identityMatrix, glm::vec3(4.55, 0.0, -2.0));
        scale1 = glm::scale(identityMatrix, glm::vec3(2.5,3.0,2.0));
        cube1.drawCubeWithTexture(lightingShaderWithTexture, modelTexture*scale1*translate1 );

        //building 2
        translate2 = glm::translate(identityMatrix, glm::vec3(4.55, 0.0, 0.0));
        scale2 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale2 * translate2);

        //building 3
        translate3 = glm::translate(identityMatrix, glm::vec3(4.55, 0.0, 2.0));
        scale3 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale3 * translate3);

        //building 4
        translate4 = glm::translate(identityMatrix, glm::vec3(6.55, 0.0, -2.0));
        scale4 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube4.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale4 * translate4);
        
        //building 5
        translate5 = glm::translate(identityMatrix, glm::vec3(6.55, 0.0, 0.0));
        scale5 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale5 * translate5);

        //building 6
        translate6 = glm::translate(identityMatrix, glm::vec3(6.55, 0.0, 2.0));
        scale6 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale6 * translate6);

        //building 7
        translate7 = glm::translate(identityMatrix, glm::vec3(8.55, 0.0, -2.0));
        scale7 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube7.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale7 * translate7);

        //building 8
        translate8 = glm::translate(identityMatrix, glm::vec3(8.55, 0.0, 0.0));
        scale8 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube8.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale8 * translate8);

        //building 9
        translate9 = glm::translate(identityMatrix, glm::vec3(8.55, 0.0, 2.0));
        scale9 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube9.drawCubeWithTexture(lightingShaderWithTexture, modelTexture * scale9 * translate9);

        //shop1
        translate10 = glm::translate(identityMatrix, glm::vec3(0.55, 0.0, -2.0));
        scale10 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube10.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* scale10* translate10);
        ////shop2
        translate11 = glm::translate(identityMatrix, glm::vec3(0.55, 0.0, 0.0));
        scale11 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube11.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* scale11* translate11);

        //////shop3
        translate12 = glm::translate(identityMatrix, glm::vec3(-1.45, 0.0, -2.0));
        scale12 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* scale12* translate12);

        //////shop3
        translate13 = glm::translate(identityMatrix, glm::vec3(-1.45, 0.0, 0.0));
        scale13 = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 2.0));
        cube13.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* scale13* translate13);

        //tree1
        translate14 = glm::translate(identityMatrix, glm::vec3(10, 1.5, -0.9));
        scale14 = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube14.drawCubeWithTexture(lightingShaderWithTexture, modelTexture*translate14*scale14);

        //road
        translate15 = glm::translate(identityMatrix, glm::vec3(-7.2, 0.0, 7.0));
        scale15 = glm::scale(identityMatrix, glm::vec3(36, 0.003, 4));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate15* scale15);

        //road2
        translate16 = glm::translate(identityMatrix, glm::vec3(5.55, 0.0, -25.0));
        scale16 = glm::scale(identityMatrix, glm::vec3(4, 0.002,50));
        cube16.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate16* scale16);

        //watch1
        translate17 = glm::translate(identityMatrix, glm::vec3(24.0, 1.6, 11.0));
        scale17 = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate17* scale17);

        //grass
        translate18 = glm::translate(identityMatrix, glm::vec3(9.0, 0, 11.0));
        scale18 = glm::scale(identityMatrix, glm::vec3(20, 0.02, 14));
        cube18.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate18* scale18);

        //floor1
        translate19 = glm::translate(identityMatrix, glm::vec3(-7.2, 0, 11.0));
        scale19 = glm::scale(identityMatrix, glm::vec3(13, 0.02, 14));
        cube19.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate19* scale19);

        //football
        translate20 = glm::translate(identityMatrix, glm::vec3(12, 0, -19.0));
        scale20 = glm::scale(identityMatrix, glm::vec3(13, 0.04, 10));
        cube20.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate20* scale20);

        //grass2
        translate18 = glm::translate(identityMatrix, glm::vec3(-7.2, 0, -25.0));
        scale18 = glm::scale(identityMatrix, glm::vec3(12.7, 0.02, 16));
        cube18.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate18* scale18);

        //floorshop
        translate22 = glm::translate(identityMatrix, glm::vec3(-7.2, 0, -9.0));
        scale22 = glm::scale(identityMatrix, glm::vec3(12.7, 0.02, 16));
        cube22.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate22* scale22);

        //floorbuilding
        translate23 = glm::translate(identityMatrix, glm::vec3(9.5, 0, -7.0));
        scale23 = glm::scale(identityMatrix, glm::vec3(19, 0.02, 14));
        cube23.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate23* scale23);

        //traffic
        translate24 = glm::translate(identityMatrix, glm::vec3(10, 1.5, 5.2));
        scale24 = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        cube24.drawCubeWithTexture(lightingShaderWithTexture, modelTexture* translate24* scale24);



        //moving object 
        angle_t += 0.5f;
        model = identityMatrix;
        moving_obj(cubeVAO, lightingShader, model , r,-1.5,0,-15);

        //flyer 
        flyer(cubeVAO, lightingShader, model, FLYER_Y,-8,0,-15);

        if (FLYER_Y_INCREASE) FLYER_Y += 0.01;
        else FLYER_Y -= 0.01;
        if (FLYER_Y > 4.8) {
            FLYER_Y = 4.8;
            FLYER_Y_INCREASE = false;
        }
        else if (FLYER_Y < 0.0) {
            FLYER_Y = 0;
            FLYER_Y_INCREASE = true;
        }

        if (fan_on)
            r += speed;
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   // Sphere sun = sphere()

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

//void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
//{
//    lightingShader.use();
//
//    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
//    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
//    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
//    lightingShader.setFloat("material.shininess", 32.0f);
//
//    lightingShader.setMat4("model", model);
//
//    glBindVertexArray(cubeVAO);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x=0,float y = 0, float z=0)
{
    float baseHeight = 0.05;
    float width = 0.5;
    float length = 1.0;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(length, baseHeight, width));
    translate = glm::translate(model, glm::vec3(-1.0+x, 0.05+y, -0.5+z));
    model = translate * scale ;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.571, 0.075);


    // leg 1

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05, baseHeight, 0.05));
    translate = glm::translate(model, glm::vec3(-0.05+x, 0.0+y, -0.5+z));
    model =  translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.571, 0.075);

    // leg 2

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05, baseHeight, 0.05));
    translate = glm::translate(model, glm::vec3(-0.05+x, 0.0+y, -0.1+z));
    model =  translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.571, 0.075);

    // leg 3

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05, baseHeight, 0.05));
    translate = glm::translate(model, glm::vec3(-1.0+x, 0.0+y, -0.5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.571, 0.075);

    // leg 4

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05, baseHeight, 0.05));
    translate = glm::translate(model, glm::vec3(-1.0+x, 0.0+y, -0.1+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.571, 0.075);



    //head
    
    glm::mat4  rotateYMatrix ;
    model = glm::mat4(1.0f);
    rotateYMatrix = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(length/2.2, baseHeight, width));
    translate = glm::translate(model, glm::vec3(0.06+x, 0.05+y, -0.5+z));
    model = rotateYMatrix * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.871, 0.075);

}

void floor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.001;
    float width = 36.0;
    float length = 50.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.2, 0, -0.5));
    model = scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.290, 0.263, 0.263);
}

void tree(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2,1.5,0.2));
    translate = glm::translate(model, glm::vec3(-0.05, 0.0, -0.5));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.451, 0.165, 0.165);

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1, 1, 1));
    translate = glm::translate(model, glm::vec3(-0.5, 1.5, -0.9));
    model =  alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.571, 0.075);
   
}

void clock1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    clock_z += deg;
    deg -= 0.00001f;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z+clock_z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.4, 0.02, 0.02));
    translate = glm::translate(model, glm::vec3(24.5, 2.1, 12.02));
    model = translate * rotateZMatrix *scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0, 0);


}
void clock2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    clock_y += deg2;
    deg2 -= 0.00001/18;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z + clock_y), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(0.3, 0.02, 0.02));
    translate = glm::translate(model, glm::vec3(24.5, 2.1, 12.02));
    model = translate * rotateZMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 0, 0);
}

void func(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x = 0,float y =0,float z =0,float g=0)
{
    //truck
    truck_z += inc;

    if (truck_z >= 24)
    {
        inc -= 0.01f;
    }
    if (truck_z <= -14)
    {
        inc += 0.01f;
    }
        

    Sphere sphere = Sphere();
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0+x, 0.2+y, truck_z + 0.0+z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(truck_angle), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.8, 0.8));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.8, 0.3);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0+x, 0.2+y, truck_z - 2.5+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.3, 2.5));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    // wheel1
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(0.0f+x, 0.2f+y, truck_z*g + 0.3f+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    //wheel2
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(1+x, 0.2+y, truck_z*g + 0.3f+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    // wheel3
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(0+x, 0.2+y, truck_z*g + 1.0f+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    //wheel4
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(1+x, 0.2+y, truck_z*g + 1.0f+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);
   /* modelForSphere = glm::translate(model, glm::vec3(0.4f, 2.5f, truck_z + 0.3f));
    modelForSphere = modelForSphere ;
    sphere.drawSphere(lightingShader, modelForSphere);


    modelForSphere = glm::translate(model, glm::vec3(1.2f, 2.5f, truck_z - 2.0f));
    modelForSphere = modelForSphere ;
    sphere.drawSphere(lightingShader, modelForSphere);

    modelForSphere = glm::translate(model, glm::vec3(1.2f, 2.5f, truck_z + 0.3f));
    modelForSphere = modelForSphere;
    sphere.drawSphere(lightingShader, modelForSphere);*/

}

void sun(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    Sphere sphere = Sphere();
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0, 0.2, 0.0));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(truck_angle), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.8, 0.8));
    model = translateMatrix * scaleMatrix;
    // wheel1
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(0.0f, 10, -20));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.5, 0.5));
    modelForSphere = modelForSphere * scaleMatrix;
    sphere.diffuse = glm::vec3(0.992, 0.718, 0.0745);
    sphere.drawSphere(lightingShader, modelForSphere);
}

void func2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 0, float y = 0, float z = 0, float g = 0)
{
    //truck
    truck_x += inc2;

    if (truck_x >= 17)
        inc2 = -0.01;
    if (truck_x <= -10)
        inc2 += 0.01;

    Sphere sphere = Sphere();
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0 + x+ truck_x, 0.2 + y,  10.0 + z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(truck_angle+90), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.8, 0.8));
    model = translateMatrix *rotateYMatrix*scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5, 0.8, 0.3);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.5 + x+ truck_x, 0.2 + y,  10 + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.3, 2.5));
    model = translateMatrix * rotateYMatrix* scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    // wheel1
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(0.0f + x+ truck_x*g, 0.2f + y, +0.3f + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * rotateYMatrix* scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    //wheel2
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(1 + x+ truck_x * g, 0.2 + y,  +0.3f + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * rotateYMatrix* scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    // wheel3
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(0 + x+truck_x*g, 0.2 + y, +1.0f + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * rotateYMatrix* scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    //wheel4
    modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(1 + x+truck_x*g, 0.2 + y,+1.0f + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.4f, 0.05f));
    modelForSphere = modelForSphere * rotateYMatrix *scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);
    /* modelForSphere = glm::translate(model, glm::vec3(0.4f, 2.5f, truck_z + 0.3f));
     modelForSphere = modelForSphere ;
     sphere.drawSphere(lightingShader, modelForSphere);


     modelForSphere = glm::translate(model, glm::vec3(1.2f, 2.5f, truck_z - 2.0f));
     modelForSphere = modelForSphere ;
     sphere.drawSphere(lightingShader, modelForSphere);

     modelForSphere = glm::translate(model, glm::vec3(1.2f, 2.5f, truck_z + 0.3f));
     modelForSphere = modelForSphere;
     sphere.drawSphere(lightingShader, modelForSphere);*/

}

void trafficlight(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x = 0,float y = 0,float z = 0)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2, 2.0, 0.2));
    translate = glm::translate(model, glm::vec3(-0.05+x, 0.0+y, -0.5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0, 0, 0);

    /*model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1, 1, 1));
    translate = glm::translate(model, glm::vec3(-0.5+x, 1.5+y, -0.9+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1, 1, 1);*/

}

void trafficlight2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 0, float y = 0, float z = 0)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2, 2.0, 0.2));
    translate = glm::translate(model, glm::vec3(-0.05 + x, 0.0 + y, 4.5 + z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0, 0, 0);

    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1, 1, 1));
    translate = glm::translate(model, glm::vec3(-0.5+x, 1.5+y, 4.1+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 1, 1, 1);

}
void roof(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x = 0,float y = 0,float z = 0)
{
    float baseHeight = 0.001;
    float width = 2.5;
    float length = 2.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(6.4+x, 3.0+y, -4.0+z));
    model = translate* scale;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);
}
void roof2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 0, float y = 0, float z = 0)
{
    float baseHeight = 0.001;
    float width = 1;
    float length = 1;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(7 + x, 2.6 + y, -4.0 + z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.090, 0.207, 0.08235);
}
void roof3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 0, float y = 0, float z = 0)
{
    float baseHeight = 0.001;
    float width = 1;
    float length = 1;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z+90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(7.0 + x, 1.6 + y, -4.0 + z));
    model = translate * rotateZMatrix* scale;
    drawCube(cubeVAO, lightingShader, model, 0.090, 0.207, 0.08235);
}
void pool(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x=0,float y =0,float z = 0)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    //front wall
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(6, 0.5, 0.2));
    translate = glm::translate(model, glm::vec3(-4+x, 0.0+y, 5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.447, 0.365, 0.448);

    //back wall
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(6, 0.5, 0.2));
    translate = glm::translate(model, glm::vec3(-4+x, 0.0+y, -5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.447, 0.365, 0.448);

    //1st side wall
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2, 0.5, 10));
    translate = glm::translate(model, glm::vec3(-4+x, 0.0+y, -5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.447, 0.365, 0.448);

    //2nd side wall
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2, 0.5, 10));
    translate = glm::translate(model, glm::vec3(2+x, 0.0+y, -5+z));
    model = translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.447, 0.365, 0.448);

}

void building(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x = 0, float z = 0)
{
    float baseHeight = 3.0;
    float width = 1.8;
    float length = 2.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(2.55+x, 0.0, 2.0 + z));
    model = scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 1, 1);
}


void mall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 0, float z = 0)
{
    float baseHeight = 2.5;
    float width = 1.8;
    float length = 3.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-3.55 + x, 0.0, 2.0 + z));
    model = scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0, 1, 0);
}

void road(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.01;
    float width = 1.0;
    float length = 12.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(3.5, 0.0, -0.5));
    model = scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) if (fan_on) speed += 0.5f;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) if (fan_on) speed -= 0.5f;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) fan_on = false;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        fan_on = true;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        if (onOffPointToggle)
        {
            pointlight1.turnOff();
            
            onOffPointToggle = false;
        }
        else
        {
            pointlight1.turnOn();
          
            onOffPointToggle = true;
        }
       // pointlight3.turnOff();
       // pointlight4.turnOff();

    }
    

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        
        if (onOffSpotToggle)
        {
           
            pointlight2.turnOff();
            onOffSpotToggle = false;
        }
        else
        {
            pointlight2.turnOn();
            onOffSpotToggle = true;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {

        if (onOffDirectToggle)
        {

            pointlight3.turnOff();
            onOffDirectToggle = false;
        }
        else
        {
            pointlight3.turnOn();
            onOffDirectToggle = true;
        }
    }
    
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            //pointlight4.turnAmbientOff();
            //pointlight1.turnDiffuseOn();
            //pointlight2.turnDiffuseOn();
            //pointlight3.turnDiffuseOn();
            //pointlight4.turnDiffuseOn();
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            //pointlight3.turnSpecularOn();
            //pointlight4.turnSpecularOn();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            //pointlight4.turnAmbientOn();
            //pointlight1.turnDiffuseOff();
            //pointlight2.turnDiffuseOff();
            //pointlight3.turnDiffuseOff();
            //pointlight4.turnDiffuseOff();
            //pointlight1.turnSpecularOff();
            //pointlight2.turnSpecularOff();
            //pointlight3.turnSpecularOff();
            //pointlight4.turnSpecularOff();
            ambientToggle = !ambientToggle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            //pointlight4.turnDiffuseOff();
            //pointlight1.turnAmbientOn();
            //pointlight2.turnAmbientOn();
            //pointlight3.turnAmbientOn();
            //pointlight4.turnAmbientOn();
            //pointlight1.turnSpecularOn();
            //pointlight2.turnSpecularOn();
            //pointlight3.turnSpecularOn();
            //pointlight4.turnSpecularOn();

            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            //pointlight4.turnDiffuseOn();
            //pointlight1.turnOff();
            //pointlight2.turnOff();
            //pointlight3.turnOff();
            //pointlight4.turnOff();

            diffuseToggle = !diffuseToggle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            //pointlight4.turnSpecularOff();
            //pointlight1.turnOff();
            //pointlight2.turnOff();
            //pointlight3.turnOff();
            //pointlight4.turnOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            //pointlight4.turnSpecularOn();
            //pointlight1.turnOff();
            //pointlight2.turnOff();
            //pointlight3.turnOff();
            //pointlight4.turnOff();
            specularToggle = !specularToggle;
        }
    }
    /*
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnEmissionOff();
            pointlight2.turnEmissionOff();
            pointlight3.turnEmissionOff();
            pointlight4.turnEmissionOff();
            emissionToggle = !emissionToggle;
        }
        else
        {
            pointlight1.turnEmissionOn();
            pointlight2.turnEmissionOn();
            pointlight3.turnEmissionOn();
            pointlight4.turnEmissionOn();
            emissionToggle = !emissionToggle;
        }
    }
    */

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOff();
        pointlight2.turnDiffuseOff();
   //     pointlight3.turnDiffuseOff();
    //    pointlight4.turnDiffuseOff();
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
    //    pointlight3.turnSpecularOn();
    //    pointlight4.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOff();
        pointlight2.turnSpecularOff();
   //     pointlight3.turnSpecularOff();
    //    pointlight4.turnDiffuseOff();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
