#include "../include/Window.hpp"
#include <iostream>

namespace Globals {
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    bool firstMouse = true;
    float lastX = WIN_WIDTH / 2.0f;
    float lastY = WIN_HEIGHT / 2.0f;
    float lastFrame = 0.0f;
    int windowWidth = static_cast<int>(WIN_WIDTH);
    int windowHeight = static_cast<int>(WIN_HEIGHT);
}

void processInputCamera(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Globals::camera.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Globals::camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Globals::camera.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Globals::camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// Callback para redimensionamento da janela
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Globals::windowWidth = width;
    Globals::windowHeight = height;
}

void mouse_callback(GLFWwindow* window,double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (Globals::firstMouse)
    {
       Globals::lastX = xpos;
       Globals::lastY = ypos;
       Globals::firstMouse = false;
    }

    float xoffset = xpos - Globals::lastX;
    float yoffset = Globals::lastY - ypos; // reversed since y-coordinates go from bottom to top

    Globals::lastX = xpos;
    Globals::lastY = ypos;

    Globals::camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window,double xoffset, double yoffset)
{
    Globals::camera.ProcessMouseScroll(static_cast<float>(yoffset));
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

    // Obtém o tamanho da tela primária
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    if (mode) {
        int screenWidth = mode->width;
        int screenHeight = mode->height;

        int posX = (screenWidth - WIN_WIDTH) / 2;
        int posY = (screenHeight - WIN_HEIGHT) / 2;

        glfwSetWindowPos(window, posX, posY);
    }

    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Ativa sincronização com o monitor (VSync)
    glfwSwapInterval(1);

    return window;
}

GLFWwindow *startWindowCamera(int width, int height, const char *title)
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

    // Obtém o tamanho da tela primária
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    if (mode) {
        int screenWidth = mode->width;
        int screenHeight = mode->height;

        int posX = (screenWidth - WIN_WIDTH) / 2;
        int posY = (screenHeight - WIN_HEIGHT) / 2;

        glfwSetWindowPos(window, posX, posY);
    }

    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Ativa sincronização com o monitor (VSync)
    glfwSwapInterval(1);

    return window;
}

// Inicializa o carregamento das funções OpenGL com GLAD
int initializeOpenGL(GLFWwindow *window, bool gl_depth_test)
{
    if (window == nullptr) {
        std::cerr << "Erro: Ponteiro da janela é nulo." << std::endl;
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erro: Falha ao inicializar GLAD." << std::endl;
        return -1;
    }

    if(gl_depth_test){

        glEnable(GL_DEPTH_TEST);
    }
    

    return 0;
}
