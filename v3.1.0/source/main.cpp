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
        menu.LoadFromFile("../config/GUI/menu_button.json");//arquivo de configs do menu

        Shader *uberSH = new Shader(DEFAULT_UBER_VERTEX, DEFAULT_UBER_FRAGMENT);

        Texture *placeholderDiffuse = new Texture("../texture/container2.png");
        Texture *placeholderSpecular = new Texture("../texture/container2_specular.png");

        //configs iniciais
        Scene scene(uberSH);
        scene.lightingEnabled = menu.findButton(Menu::TypeButton::LIGHT)->toggle;
        scene.AddObject(menu.findButton(Menu::TypeButton::ADD_OBJ)->primitiveType);
        int selectedIndex = -1;
        selectedIndex = (int)scene.GetObjects().size() - 1;


        bool mouseOverUI;
        bool rightMouseHeld;
        bool middleMouseHeld;

        while (!glfwWindowShouldClose(window))
        {
            // Iniciando configurações da janela e overlay
            glm::mat4 projection, view;
            updateFrameCamera(window, projection, view);

            glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGuiOverlay::Begin();

            // Controle de eventos do mouse
            mouseOverUI = ImGui::GetIO().WantCaptureMouse;
            rightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

            if (rightMouseHeld && !mouseOverUI)

                SetCameraControl(window, true);

            else if (!rightMouseHeld && Globals::cameraControlEnabled)

                SetCameraControl(window, false);

            middleMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
            UpdatePan(window, middleMouseHeld && !mouseOverUI);
        


            //renderizaçõa e execução dos menus e botoes
            float menuBarHeight = 0.0f;
            if (ImGui::BeginMainMenuBar())
            {
                menuBarHeight = ImGui::GetFrameHeight();

                Menu::Button *actionBtt = menu.Render();

                if (actionBtt != nullptr)
                {
                    switch (actionBtt->type)
                    {
                        case Menu::TypeButton::NEW:
                            std::cout << "[Action] Criando novo projeto...\n";
                            break;

                        case Menu::TypeButton::OPEN:
                            std::cout << "[Action] Abrindo projeto...\n";
                            break;

                        case Menu::TypeButton::SAVE:
                            std::cout << "[Action] Salvando projeto...\n";
                            break;

                        case Menu::TypeButton::OPEN_OBJ:
                            std::cout << "[Action] arquivo OBJ...\n";
                            break;

                        case Menu::TypeButton::ADD_OBJ:
                           
                            scene.AddObject(actionBtt->primitiveType);
                            selectedIndex = (int)scene.GetObjects().size() - 1;
                            break;

                        case Menu::TypeButton::EXPORT:
                            std::cout << "[Action] Export...\n";
                            break;

                        case Menu::TypeButton::DELETE:
                            std::cout << "[Action] Delete...\n";
                            break;

                        case Menu::TypeButton::OPEN_TEX:
                            std::cout << "[Action] Load texture...\n";
                            break;

                        case Menu::TypeButton::GIZMO_OBJ:
                            std::cout << "[Action] Show Gizmo...\n";
                            break;

                        case Menu::TypeButton::LIGHT:
                            std::cout << "[Action] Toogle light...\n";
                            scene.lightingEnabled = actionBtt->toggle;
                            break;

                        case Menu::TypeButton::GRID:
                            std::cout << "[Action] Grid enable...\n";
                            break;

                        case Menu::TypeButton::METRICS:
                            std::cout << "[Action] Metrics...\n";
                            break;

                        case Menu::TypeButton::GIZMO_CAM:
                            std::cout << "[Action] Gizmo enable...\n";
                            break;

                        case Menu::TypeButton::POS_FIRST:
                            std::cout << "[Action] Reset Position...\n";
                            break;

                        default:
                            break;
                    }
                }

                ImGui::EndMainMenuBar();
            }
            

            

            auto &objects = scene.GetObjects();

            // PAINEL HIERARCHY
            ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(260, 300), ImGuiCond_FirstUseEver);
            
            ImGui::Begin("Hierarchy");

            for (int i = 0; i < (int)objects.size(); i++)
            {
                bool isSelected = (selectedIndex == i);
                if (ImGui::Selectable(objects[i].name.c_str(), isSelected))
                    selectedIndex = i;
            }

            ImGui::Separator();
            ImGui::TextDisabled(Globals::cameraControlEnabled
                                    ? "Camera ativa (botao direito)"
                                    : (Globals::panActive ? "Pan ativo (botao do meio)" : "UI ativa"));

            ImGui::End();

            // PAINEL SCENE SETTINGS
            if (scene.lightingEnabled)
            {
                ImGui::SetNextWindowPos(ImVec2(0, menuBarHeight + 320.0f), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(260, 200), ImGuiCond_FirstUseEver);
                ImGui::Begin("Scene Settings");

                ImGui::Text("Light");
                ImGui::DragFloat3("Light Position", &scene.light.position.x, 0.05f, -20.0f, 20.0f);
                ImGui::ColorEdit3("Light Ambient", &scene.light.ambient.x);
                ImGui::ColorEdit3("Light Diffuse", &scene.light.diffuse.x);
                ImGui::ColorEdit3("Light Specular", &scene.light.specular.x);

                ImGui::End();
            }

            // PAINEL INSPECTOR
            if (selectedIndex >= 0 && selectedIndex < (int)objects.size())
            {
                SceneObject &sel = objects[selectedIndex];

                bool inspectorOpen = true;
                ImGui::SetNextWindowPos(ImVec2(Globals::windowWidth - 340.0f, menuBarHeight), ImGuiCond_Always);
                ImGui::SetNextWindowSize(ImVec2(340, 480), ImGuiCond_FirstUseEver);

                ImGui::Begin("Inspector", &inspectorOpen);

                ImGui::Text("%s", sel.name.c_str());
                ImGui::Separator();

                // Transform
                ImGui::DragFloat3("Position", &sel.position.x, 0.05f, -20.0f, 20.0f);
                ImGui::DragFloat3("Rotation", &sel.rotation.x, 1.0f, -180.0f, 180.0f);
                ImGui::DragFloat3("Scale", &sel.scale.x, 0.05f, 0.01f, 10.0f);

                ImGui::Separator();

                // Aparência
                ImGui::ColorEdit3("Color", &sel.color.x);
                ImGui::Checkbox("Use Texture", &sel.useTexture);
                if (sel.useTexture)
                {
                    sel.diffuseTex = placeholderDiffuse;
                    sel.specularTex = placeholderSpecular;
                }
                else
                {
                    sel.diffuseTex = nullptr;
                    sel.specularTex = nullptr;
                }

                // Ambient/Specular/Shininess
                if (scene.lightingEnabled)
                {
                    ImGui::DragFloat("Shininess", &sel.shininess, 1.0f, 1.0f, 256.0f);
                    if (!sel.useTexture)
                    {
                        ImGui::ColorEdit3("Ambient", &sel.ambient.x);
                        ImGui::ColorEdit3("Specular", &sel.specular.x);
                    }
                }

                // Geometria específica
                bool geometryChanged = false;

                switch (sel.type)
                {
                case PrimitiveTypeObj::Sphere:
                    ImGui::Separator();
                    ImGui::Text("Sphere Geometry");
                    geometryChanged |= ImGui::DragFloat("Radius", &sel.radius, 0.05f, 0.05f, 10.0f);
                    geometryChanged |= ImGui::SliderInt("Slices", &sel.slices, 3, 128);
                    geometryChanged |= ImGui::SliderInt("Stacks", &sel.stacks, 2, 64);
                    break;

                case PrimitiveTypeObj::Circle:
                    ImGui::Separator();
                    ImGui::Text("Circle Geometry");
                    geometryChanged |= ImGui::DragFloat("Radius", &sel.radius, 0.05f, 0.05f, 10.0f);
                    geometryChanged |= ImGui::SliderInt("Segments", &sel.slices, 3, 128);
                    break;

                case PrimitiveTypeObj::Cylinder:
                    ImGui::Separator();
                    ImGui::Text("Cylinder Geometry");
                    geometryChanged |= ImGui::DragFloat("Base Radius", &sel.baseRadius, 0.05f, 0.0f, 10.0f);
                    geometryChanged |= ImGui::DragFloat("Top Radius", &sel.topRadius, 0.05f, 0.0f, 10.0f);
                    geometryChanged |= ImGui::DragFloat("Height", &sel.height, 0.05f, 0.05f, 20.0f);
                    geometryChanged |= ImGui::SliderInt("Slices", &sel.slices, 3, 128);
                    geometryChanged |= ImGui::SliderInt("Stacks", &sel.stacks, 1, 64);
                    geometryChanged |= ImGui::Checkbox("Cap Bottom", &sel.capBottom);
                    geometryChanged |= ImGui::Checkbox("Cap Top", &sel.capTop);
                    break;

                case PrimitiveTypeObj::Paraboloid:
                    ImGui::Separator();
                    ImGui::Text("Paraboloid Geometry");
                    geometryChanged |= ImGui::DragFloat("Radius", &sel.radius, 0.05f, 0.05f, 10.0f);
                    geometryChanged |= ImGui::DragFloat("Height", &sel.height, 0.05f, 0.05f, 20.0f);
                    geometryChanged |= ImGui::SliderInt("Slices", &sel.slices, 3, 128);
                    geometryChanged |= ImGui::SliderInt("Stacks", &sel.stacks, 1, 64);
                    geometryChanged |= ImGui::Checkbox("Cap Bottom", &sel.capBottom);
                    geometryChanged |= ImGui::Checkbox("Cap Top", &sel.capTop);
                    break;

                case PrimitiveTypeObj::Cube:
                case PrimitiveTypeObj::Triangle:
                case PrimitiveTypeObj::Square:
                    break;
                }

                if (geometryChanged)
                    scene.RegenerateMesh(sel);

                ImGui::Separator();
                if (ImGui::Button("Remove Object"))
                {
                    scene.RemoveObject(selectedIndex);
                    selectedIndex = -1;
                    inspectorOpen = false;
                }

                ImGui::End();

                if (!inspectorOpen)
                    selectedIndex = -1;
            }

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