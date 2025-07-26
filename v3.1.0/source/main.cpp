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

        Shader *cubeSH = new Shader("../shader/light/maps/specular/map_spec.vs","../shader/light/maps/specular/map_spec.fs");
        Shader *lampSH = new Shader("../shader/light/lamp.vs","../shader/light/lamp.fs");
        Texture *diffuseMap = new Texture("../texture/container2.png");
        Texture *specularMap = new Texture("../texture/container2_specular.png");
        Mesh   *mesh = Mesh::cubeMesh(true,true);

        Shape cube(mesh,true,true);
        Shape lamp(mesh,false,false);
        mesh->clearCPUData();

        glm::mat4 model_cube = glm::mat4(1.0f);

        glm::mat4 model_lamp = glm::mat4(1.0f);
        model_lamp = glm::translate(model_cube,lightPos);
        model_lamp = glm::scale(model_lamp,glm::vec3(0.5f));
        
        cubeSH->useShaders();
        cubeSH->setInt("material.diffuse", 0);
        cubeSH->setInt("material.specular", 1);

        // Loop principal de renderização
        while (!glfwWindowShouldClose(window))
        {   
            glm::mat4 projection, view;
            updateFrameCamera(window,projection,view);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            lampSH->useShaders();
            lampSH->setMat4("projection",projection);
            lampSH->setMat4("view",view);
            lampSH->setMat4("model",model_lamp);

            lamp.desenharElem();


            cubeSH->useShaders();
            cubeSH->setVec3("light.position", lightPos);
            cubeSH->setVec3("viewPos", Globals::camera.Position);

            cubeSH->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            cubeSH->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            cubeSH->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            cubeSH->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
            cubeSH->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
            cubeSH->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
            cubeSH->setFloat("material.shininess", 32.0f);

            cubeSH->setMat4("projection",projection);
            cubeSH->setMat4("view",view);
            cubeSH->setMat4("model",model_cube);

            diffuseMap->Bind();
            specularMap->Bind(GL_TEXTURE1);

            cube.desenharElem();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete cubeSH;
        delete lampSH;
        delete mesh;
        delete diffuseMap;
        delete specularMap;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
