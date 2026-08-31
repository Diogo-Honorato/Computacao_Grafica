#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include "../dep/glad/include/glad/glad.h"
#include "../dep/glfw/include/GLFW/glfw3.h"
#include "../include/Camera.hpp"

#define WIN_WIDTH 1920.0
#define WIN_HEIGHT 1080.0
#define RATIO (float)(WIN_WIDTH/WIN_HEIGHT)

namespace Globals {
    extern Camera camera;
    extern bool firstMouse;
    extern float lastX;
    extern float lastY;
    extern float lastFrame;
    extern int windowWidth;
    extern int windowHeight;
    extern bool cameraControlEnabled; // true = mouse controla a câmera (travado); false = mouse livre pra UI

    // Estado do pan (arrastar com o botão do meio)
    extern bool panActive;
    extern double panLastX;
    extern double panLastY;
}

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow *startWindow(int width, int height, const char *title);
GLFWwindow *startWindowCamera(int width, int height, const char *title);
int initializeOpenGL(GLFWwindow *window,bool gl_depth_test);
void processInputCamera(GLFWwindow *window, float deltaTime);
void mouse_callback(GLFWwindow* window,double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window,double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Ativa/desativa o controle da câmera pelo mouse, ajustando o modo do cursor.
inline void SetCameraControl(GLFWwindow* window, bool enabled)
{
    if (enabled == Globals::cameraControlEnabled)
        return;
        
    Globals::cameraControlEnabled = enabled;
    glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

    if (enabled)
        Globals::firstMouse = true; // evita "pulo" da câmera ao reativar
}


inline void UpdatePan(GLFWwindow* window, bool wantsPan)
{
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);

    if (wantsPan && !Globals::panActive)
    {

        Globals::panActive = true;
        Globals::panLastX = mx;
        Globals::panLastY = my;
        return;
    }

    if (!wantsPan)
    {
        Globals::panActive = false;
        return;
    }

    float xoffset = static_cast<float>(mx - Globals::panLastX);
    float yoffset = static_cast<float>(my - Globals::panLastY);

    Globals::camera.ProcessMousePan(xoffset, yoffset);

    Globals::panLastX = mx;
    Globals::panLastY = my;
}

inline void updateFrameCamera(GLFWwindow* window, glm::mat4& projection, glm::mat4& view) {
    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - Globals::lastFrame;
    Globals::lastFrame = currentFrame;

    processInputCamera(window, deltaTime);

    float aspectRatio = static_cast<float>(Globals::windowWidth) / static_cast<float>(Globals::windowHeight);
    projection = glm::perspective(glm::radians(Globals::camera.Zoom), aspectRatio, 0.1f, 100.0f);
    view = Globals::camera.GetViewMatrix();
}

#endif