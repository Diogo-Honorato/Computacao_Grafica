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
        glm::vec3 lightPos(1.2f, 1.0f, -2.0f);

        Shader *cubeSH = new Shader("../shader/light/light.vs","../shader/light/light.fs");
        Shader *lampSH = new Shader("../shader/light/lamp.vs","../shader/light/lamp.fs");
        Mesh   *mesh = Mesh::sphereMesh(false,true);

        Shape cube(mesh,cubeSH,nullptr,true);
        Shape lamp(mesh,lampSH,nullptr,true);
        mesh->clearCPUData();

        glm::mat4 model_cube = glm::mat4(1.0f);

        glm::mat4 model_lamp = glm::mat4(1.0f);
        model_lamp = glm::translate(model_cube,lightPos);
        model_lamp = glm::scale(model_lamp,glm::vec3(0.5f));
            
        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            glm::mat4 projection, view;
            updateFrameCamera(window,projection,view);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            lamp.getShader()->useShaders();
            lamp.getShader()->setMat4("projection",projection);
            lamp.getShader()->setMat4("view",view);
            lamp.getShader()->setMat4("model",model_lamp);

            lamp.desenharElem();


            cube.getShader()->useShaders();
            cube.getShader()->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
            cube.getShader()->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            cube.getShader()->setVec3("lightPos", lightPos);
            cube.getShader()->setVec3("viewPos", Globals::camera.Position);
    
            cube.getShader()->setMat4("projection",projection);
            cube.getShader()->setMat4("view",view);
            cube.getShader()->setMat4("model",model_cube);

            cube.desenharElem();


            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete cubeSH;
        delete lampSH;
        delete mesh;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
