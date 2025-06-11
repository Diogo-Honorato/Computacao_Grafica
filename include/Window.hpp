#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include "../dep/glad/include/glad/glad.h"
#include "../dep/glfw/include/GLFW/glfw3.h"

#define WIN_WIDTH 800.0
#define WIN_HEIGHT 600.0
#define RATIO (float)(WIN_WIDTH/WIN_HEIGHT)

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
GLFWwindow *startWindow(int width, int height, const char *title);
int initializeOpenGL(GLFWwindow *window);

#endif