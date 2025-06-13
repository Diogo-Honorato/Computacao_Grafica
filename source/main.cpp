#include "../include/main.hpp"

/*
    Press key:
        'esc' activates: Close window.
        'w'   activates: glPolygonMode FILL.
        'e'   activates: glPolygonMode LINE.
        'r'   activates: glPolygonMode POINT.

*/

int main()
{
    // Cria janela
    GLFWwindow *window = startWindow(WIN_WIDTH, WIN_HEIGHT, "Engine");
    if (initializeOpenGL(window, true) == -1)
    {
        return -1;
    }

    {
        Cube cube;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),RATIO,0.1f,100.0f);

        
        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // Limpa tela
            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model,(float)glfwGetTime()*glm::radians(45.0f),glm::vec3(0.7f,1.0f,0.0f));

            cube.getShader().useShaders();
            cube.getShader().setInt("ourTexture", 0);
            cube.getShader().setMat4("model",model);
            cube.getShader().setMat4("view",view);
            cube.getShader().setMat4("projection",projection);
            cube.desenhar();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}