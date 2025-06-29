#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include "../dep/glad/include/glad/glad.h"
#include "../dep/glfw/include/GLFW/glfw3.h"
#include "../include/Camera.hpp"

#define WIN_WIDTH 800.0
#define WIN_HEIGHT 600.0
#define RATIO (float)(WIN_WIDTH/WIN_HEIGHT)

namespace Globals {
    extern Camera camera;
    extern bool firstMouse;
    extern float lastX;
    extern float lastY;
    extern float lastFrame;
    extern int windowWidth;
    extern int windowHeight;
}

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow *startWindow(int width, int height, const char *title);
GLFWwindow *startWindowCamera(int width, int height, const char *title);
int initializeOpenGL(GLFWwindow *window,bool gl_depth_test);
void processInputCamera(GLFWwindow *window, float deltaTime);
void mouse_callback(GLFWwindow* window,double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window,double xoffset, double yoffset);


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