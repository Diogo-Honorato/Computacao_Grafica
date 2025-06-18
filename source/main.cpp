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
        std::vector<glm::vec3> torusPoints;
        torusPoints = Pipe::generateTorus(50,2.5f);

        Pipe pipe(torusPoints, 1.0f, 1.0f);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), RATIO, 0.1f, 100.0f);

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // Limpa tela
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

            pipe.getShader().useShaders();
            pipe.getShader().setInt("ourTexture", 0);
            pipe.getShader().setMat4("model", model);
            pipe.getShader().setMat4("view", view);
            pipe.getShader().setMat4("projection", projection);
            pipe.desenhar();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}