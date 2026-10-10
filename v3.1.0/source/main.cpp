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

    //iniciando file dialog
    NFD_Init();

    //iniciando um novo frame buffer para selecionar objetos da cena com mouse
    Gui::MousePicking::setupFrameBufferPicking(Globals::windowWidth,Globals::windowHeight);

    {
        // menu principal e iniciação das configurações da engine
        Gui::Menu::MenuButton menu;
        menu.loadFromFile(INIT_FILE_MENU);//arquivo de configs do menu
        auto bttPtr = menu.findButton(Gui::Menu::TypeButton::ADD_OBJ);//gera botao extra
        if (bttPtr != nullptr) {
    
            Gui::Menu::Panel::subButtonAdd = bttPtr->subButton;
        } else {
            std::cerr << "[ERROR]: Not Found in JSON!" << std::endl;
        }
        
        Shader *mousePickSH = new Shader(DEFAULT_MOUSE_PICKING_VERTEX,DEFAULT_MOUSE_PICKING_FRAGMENT);
        Shader *uberSH = new Shader(DEFAULT_UBER_VERTEX, DEFAULT_UBER_FRAGMENT);
        
        
        //Iniciar um Projeto
        Project proj;
        bool showNewProjectScreen = false;

        std::string projectInitPath = Project::loadProjectInit();

        if (!projectInitPath.empty())
        {
            if (!proj.loadProject(projectInitPath, uberSH)){

                Gui::Menu::Panel::isOpenNewProject = true;

            }else{
                Gui::Menu::Panel::isFirstOpenNewProject = false;
            }
        }
        else
        {
            Gui::Menu::Panel::isOpenNewProject = true;
        }


        //mouse variables
        bool mouseOverUI;
        bool rightMouseHeld;
        bool middleMouseHeld;

        //in exit button
        Globals::onCloseRequested = [&proj,window]() -> bool
        {
            if (!proj.getWasSaved())
            {
                Gui::Menu::Panel::isOpenExitConfirm = true;
                return false;
            }
            return true;
        };


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
        

            //New Project Fuction
            Gui::Menu::Panel::newProject(proj,uberSH);
            
            //Load Project 
            Gui::Menu::Panel::loadProject(proj, uberSH);

            //Exit Project 
            Gui::Menu::Panel::exitConfirm(proj,window);

            //It only starts if you create or load a project
            if(!Gui::Menu::Panel::isOpenNewProject && !Gui::Menu::Panel::isFirstOpenNewProject){

                //renderização e execução dos menus e botoes
                menu.renderMenu(proj);

                //Panel HIERARCHY
                Gui::Menu::Panel::hierarchyConfig(proj.getCurrentScene());

                // PAINEL SCENE SETTINGS
                Gui::Menu::Panel::sceneConfig(proj);

                // PAINEL PROPERTIES
                Gui::Menu::Panel::propertiesConfig(proj);

                //GUIZMO
                Gui::Guizmo::drawGuizmo(proj.getCurrentScene(),projection, view);

                //Metrics
                Gui::Menu::Panel::showMetrics(proj.getCurrentScene());

                //load SCene
                Gui::Menu::Panel::loadScene(proj, uberSH);

                //Popup saved
                Gui::Menu::Panel::savePopup();


                // RENDERIZAÇÃO DA CENA
                for (auto &obj : proj.getCurrentScene().GetObjects())
                {

                    obj.shader->useShaders();
                    obj.shader->setMat4("projection", projection);
                    obj.shader->setMat4("view", view);
                    obj.shader->setMat4("model", obj.GetModelMatrix());


                    
                    obj.diffuseTex->Bind(GL_TEXTURE0);
                    obj.specularTex->Bind(GL_TEXTURE1);
                    obj.shader->setInt("diffuseMap", 0);
                    obj.shader->setInt("specularMap", 1);

                    obj.shader->setVec3("material.ambient", obj.ambient);
                    obj.shader->setVec3("material.diffuse", obj.color);
                    obj.shader->setVec3("material.specular", obj.specular);
                    obj.shader->setFloat("material.shininess", obj.shininess);


                    obj.shader->setBool("useLighting", proj.getCurrentScene().lightingEnabled);

                    if (proj.getCurrentScene().lightingEnabled)
                    {
                        obj.shader->setVec3("viewPos", Globals::camera.Position);
                        obj.shader->setVec3("light.position", proj.getCurrentScene().light.position);
                        obj.shader->setVec3("light.ambient", proj.getCurrentScene().light.ambient);
                        obj.shader->setVec3("light.diffuse", proj.getCurrentScene().light.diffuse);
                        obj.shader->setVec3("light.specular", proj.getCurrentScene().light.specular);
                    }

                    obj.shape->drawObject();
                }

                // fonte de luz
                if (proj.getCurrentScene().lightingEnabled)
                {
                    glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), proj.getCurrentScene().light.position);
                    lightModel = glm::scale(lightModel, glm::vec3(0.2f));

                    
                    uberSH->useShaders();
                    uberSH->setMat4("projection", projection);
                    uberSH->setMat4("view", view);
                    uberSH->setMat4("model", lightModel);
                    proj.getCurrentScene().getTexture(DEFAULT_DIFFUSE_TEXTURE)->Bind(GL_TEXTURE0);
                    uberSH->setBool("useLighting", false);
                    uberSH->setVec3("material.diffuse", proj.getCurrentScene().light.diffuse);

                    proj.getCurrentScene().light.cubeShape->drawObject();
                }

                //mouse picking render
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !mouseOverUI)
                {   
                    double mouseX, mouseY;
                    glfwGetCursorPos(window, &mouseX, &mouseY);

                    proj.getCurrentScene().selectedIndex = Gui::MousePicking::objectPicking((int)mouseX,(int)mouseY,Globals::windowHeight,proj.getCurrentScene().GetObjects(),mousePickSH,projection,view);
                    
                }
            }

            ImGuiOverlay::End();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete uberSH;
        delete mousePickSH;
    }

    ImGuiOverlay::Shutdown();
    NFD_Quit();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}