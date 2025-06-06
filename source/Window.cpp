#include "../include/Window.hpp"
#include <iostream>

// Trata entrada de teclado
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// Callback para redimensionamento da janela
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Inicializa GLFW, cria a janela e configura o contexto OpenGL
GLFWwindow *startWindow(int width, int height, const char *title)
{
    if (!glfwInit()) {
        std::cerr << "Erro: Falha ao inicializar GLFW!" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Erro: Falha ao criar janela GLFW!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Ativa sincronização com o monitor (VSync)
    glfwSwapInterval(1);

    return window;
}

// Inicializa o carregamento das funções OpenGL com GLAD
int initializeOpenGL(GLFWwindow *window)
{
    if (window == nullptr) {
        std::cerr << "Erro: Ponteiro da janela é nulo." << std::endl;
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erro: Falha ao inicializar GLAD." << std::endl;
        return -1;
    }

    return 0;
}
