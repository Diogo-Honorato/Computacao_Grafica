#include "../include/main.hpp"

/*
    Teclas de controle:
        - W, A, S, D: Movimento da câmera (frente, trás, esquerda, direita).
        - Botão direito do mouse (segurar): ativa o controle/rotação da câmera.
        - Botão do meio do mouse (segurar + arrastar): pan (desloca a câmera lateralmente).
        - Scroll: Controla zoom (campo de visão, quando a câmera está ativa).
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

    ImGuiOverlay::Init(window);

    {
        // menu principal
        Menu::MenuButton menu;
        menu.loadFromFile("../config/GUI/menu_button.json");//arquivo de configs do menu


        Shader *uberSH = new Shader(DEFAULT_UBER_VERTEX, DEFAULT_UBER_FRAGMENT);

        Texture *placeholderDiffuse = new Texture("../texture/container2.png");
        Texture *placeholderSpecular = new Texture("../texture/container2_specular.png");


        //configs iniciais e start da cena
        Scene scene(uberSH);
        scene.lightingEnabled = true;
        scene.AddObject(PrimitiveTypeObj::Cube);
        auto &objects = scene.GetObjects();
        scene.selectedIndex = (int)objects.size() - 1;


        //mouse variables
        bool mouseOverUI;
        bool rightMouseHeld;
        bool middleMouseHeld;



        //main render loop
        while (!glfwWindowShouldClose(window))
        {
            // Iniciando configurações da janela e overlay
            glm::mat4 projection, view;
            updateFrameCamera(window, projection, view);

            glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGuiOverlay::Begin();

            ImGuiID dockspaceID = ImGui::GetID("DockSpace");
            ImGui::DockSpaceOverViewport(dockspaceID, ImGui::GetMainViewport(),ImGuiDockNodeFlags_PassthruCentralNode);


            // Controle de eventos do mouse
            mouseOverUI = ImGui::GetIO().WantCaptureMouse;
            rightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

            if (rightMouseHeld && !mouseOverUI)

                SetCameraControl(window, true);

            else if (!rightMouseHeld && Globals::cameraControlEnabled)

                SetCameraControl(window, false);

            middleMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
            UpdatePan(window, middleMouseHeld && !mouseOverUI);
        


            //renderização e execução dos menus e botoes
            menu.renderMenu(scene);

            //Panel HIERARCHY
            Menu::Panel::hierarchyConfig(scene);

            // PAINEL SCENE SETTINGS
            Menu::Panel::sceneConfig(scene);

            // PAINEL PROPERTIES
            Menu::Panel::propertiesConfig(scene,placeholderDiffuse,placeholderSpecular);

            


            // RENDERIZAÇÃO DA CENA
            for (auto &obj : objects)
            {
                obj.shader->useShaders();
                obj.shader->setMat4("projection", projection);
                obj.shader->setMat4("view", view);
                obj.shader->setMat4("model", obj.GetModelMatrix());

                obj.shader->setBool("useTexture", obj.useTexture);
                if (obj.useTexture && obj.diffuseTex && obj.specularTex)
                {
                    obj.diffuseTex->Bind(GL_TEXTURE0);
                    obj.specularTex->Bind(GL_TEXTURE1);
                    obj.shader->setInt("diffuseMap", 0);
                    obj.shader->setInt("specularMap", 1);
                }
                else
                {
                    obj.shader->setVec3("material.ambient", obj.ambient);
                    obj.shader->setVec3("material.diffuse", obj.color);
                    obj.shader->setVec3("material.specular", obj.specular);
                }
                obj.shader->setFloat("material.shininess", obj.shininess);

                obj.shader->setBool("useLighting", scene.lightingEnabled);
                if (scene.lightingEnabled)
                {
                    obj.shader->setVec3("viewPos", Globals::camera.Position);
                    obj.shader->setVec3("light.position", scene.light.position);
                    obj.shader->setVec3("light.ambient", scene.light.ambient);
                    obj.shader->setVec3("light.diffuse", scene.light.diffuse);
                    obj.shader->setVec3("light.specular", scene.light.specular);
                }

                obj.shape->desenharElem();
            }

            // fonte de luz
            if (scene.lightingEnabled)
            {
                glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), scene.light.position);
                lightModel = glm::scale(lightModel, glm::vec3(0.2f));

                uberSH->useShaders();
                uberSH->setMat4("projection", projection);
                uberSH->setMat4("view", view);
                uberSH->setMat4("model", lightModel);
                uberSH->setBool("useTexture", false);
                uberSH->setBool("useLighting", false);
                uberSH->setVec3("material.diffuse", scene.light.diffuse);

                Shape *sphereShape = scene.GetPrimitiveShape(PrimitiveTypeObj::Sphere);
                sphereShape->desenharElem();
            }

            ImGuiOverlay::End();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete uberSH;
        delete placeholderDiffuse;
        delete placeholderSpecular;
    }

    ImGuiOverlay::Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}