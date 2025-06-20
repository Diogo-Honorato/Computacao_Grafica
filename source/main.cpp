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
        std::vector<std::unique_ptr<Shape>> Shapes;
        std::vector<glm::mat4> matrices;

        //cube
        Shapes.push_back(std::make_unique<Cube>());
        
        glm::mat4 model_body = glm::mat4(1.0);
        model_body = glm::translate(model_body,glm::vec3(0.0,0.0,-4.0));
        model_body = glm::scale(model_body,glm::vec3(3.0,4.0,1.0));
        
        matrices.push_back(model_body);


        //cone
        Shapes.push_back(std::make_unique<AxialExtruder>(0.0f));
        
        glm::mat4 model_right_arm = glm::mat4(1.0);
        model_right_arm = glm::translate(model_right_arm,glm::vec3(4.0,0.0,-4.0));
        model_right_arm = glm::scale(model_right_arm,glm::vec3(3.0,4.0,1.0));
        
        matrices.push_back(model_right_arm);


        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            float currentFrame = static_cast<float>(glfwGetTime());
            processInputCamera(window,currentFrame - Globals::lastFrame);
            Globals::lastFrame = currentFrame;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float aspectRatio = static_cast<float>(Globals::windowWidth) / static_cast<float>(Globals::windowHeight);
            glm::mat4 projection = glm::perspective(glm::radians(Globals::camera.Zoom), aspectRatio, 0.1f, 100.0f);
            glm::mat4 view = Globals::camera.GetViewMatrix();

            for (size_t i = 0; i < Shapes.size(); i++)
            {
                Shapes[i]->getShader().useShaders();

                Shapes[i]->getShader().setMat4("model", matrices[i]);
                Shapes[i]->getShader().setMat4("projection",projection);
                Shapes[i]->getShader().setMat4("view", view);

                Shapes[i]->desenhar();
            }

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}