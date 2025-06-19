#include "../include/main.hpp"

/*
    Teclas de controle:
        - ESC: Fecha a janela.
        - W, A, S, D: Movimento da câmera (frente, trás, esquerda, direita).
        - Mouse: Controla rotação da câmera.
        - Scroll: Controla zoom (campo de visão).
        - Q: Define modo de renderização como preenchido (GL_FILL).
        - E: Define modo de renderização como wireframe (GL_LINE).
        - R: Define modo de renderização como pontos (GL_POINT).
*/

int main()
{
    // Cria janela
    GLFWwindow *window = startWindowCamera(WIN_WIDTH, WIN_HEIGHT, "Engine");
    if (initializeOpenGL(window, true) == -1)
    {
        return -1;
    }

    {
        std::vector<glm::vec3> torusPoints;
        torusPoints = Pipe::generateTorus(10,2.5f);
        Pipe pipe(torusPoints, 1.0f, 1.0f);

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            float currentFrame = static_cast<float>(glfwGetTime());
            processInputCamera(window,currentFrame - Globals::lastFrame);
            Globals::lastFrame = currentFrame;

            // Limpa tela
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            float aspectRatio = static_cast<float>(Globals::windowWidth) / static_cast<float>(Globals::windowHeight);
            
            glm::mat4 projection = glm::perspective(glm::radians(Globals::camera.Zoom), aspectRatio, 0.1f, 100.0f);
            glm::mat4 view = Globals::camera.GetViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model,glm::radians(45.0f) * currentFrame, glm::vec3(0.0f,0.0f,-5.0f));

            pipe.getShader().useShaders();
            pipe.getShader().setMat4("view", view);
            pipe.getShader().setMat4("projection", projection);
            pipe.getShader().setMat4("model", model);
            pipe.getShader().setInt("ourTexture", 0);
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