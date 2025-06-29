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
        std::vector<std::unique_ptr<Shape>> shapes;
        std::vector<std::unique_ptr<glm::mat4>> matrices;
        glm::vec3 cubePos(2.0f, 0.0f,0.0);
        glm::vec3 lightPos(1.0f, 1.0f, -2.0f);

        shapes.push_back(std::make_unique<Cube>("",DEFAULT_CUBE_VERTEX,"../shader/light/cube.fs"));
        shapes.push_back(std::make_unique<Cube>("",DEFAULT_CUBE_VERTEX,"../shader/light/lamp.fs"));
        
        glm::mat4 model_cube = glm::mat4(1.0f);
        model_cube = glm::translate(model_cube, cubePos);
        
        glm::mat4 model_lamp = glm::mat4(1.0f);
        model_lamp = glm::translate(model_lamp, lightPos);
        model_lamp = glm::scale(model_lamp, glm::vec3(0.5f));
        
        matrices.push_back(std::make_unique<glm::mat4>(model_cube));
        matrices.push_back(std::make_unique<glm::mat4>(model_lamp));

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            glm::mat4 projection, view;
            updateFrameCamera(window,projection,view);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            
            for(size_t i = 0; i < shapes.size();i++){

                shapes[i]->getShader().useShaders();
                shapes[i]->getShader().setMat4("model", *matrices[i]);
                shapes[i]->getShader().setMat4("projection", projection);
                shapes[i]->getShader().setMat4("view", view);

                shapes[0]->getShader().setVec3("objectColor", 1.0f, 0.5f, 0.31f);
                shapes[0]->getShader().setVec3("lightColor",  1.0f, 1.0f, 1.0f);

                shapes[i]->desenhar();
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