#include "../include/main.hpp"

/*
    Teclas de controle:
        - ESC: Fecha a janela.
        - W, A, S, D: Movimento da câmera (frente, trás, esquerda, direita).
        - Botão direito do mouse (segurar): ativa o controle da câmera.
        - TAB: alterna entre controle de câmera e controle da UI.
        - Mouse: Controla rotação da câmera (quando ativa).
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
        Shader *cubeSH = new Shader(DEFAULT_CUBE_VERTEX, DEFAULT_CUBE_FRAGMENT);
        Mesh *mesh = Mesh::cubeMesh(false, false);
        Shape cube(mesh, false, false);
        mesh->clearCPUData();

        std::vector<SceneObject> sceneObjects;

        SceneObject cubeObj;
        cubeObj.name = "Cube";
        cubeObj.shape = &cube;
        cubeObj.shader = cubeSH;
        sceneObjects.push_back(cubeObj);

        int selectedIndex = 0;


        while (!glfwWindowShouldClose(window))
        {
            glm::mat4 projection, view;
            updateFrameCamera(window, projection, view);

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGuiOverlay::Begin();

            bool rightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
            bool mouseOverUI = ImGui::GetIO().WantCaptureMouse;

            if (rightMouseHeld && !mouseOverUI)
                SetCameraControl(window, true);
            else if (!rightMouseHeld && Globals::cameraControlEnabled)
                SetCameraControl(window, false);

            ImGui::SetNextWindowSize(ImVec2(320, 260), ImGuiCond_FirstUseEver);
            ImGui::Begin("Inspector");


            ImGui::Text("Scene Objects");
            for (int i = 0; i < (int)sceneObjects.size(); i++)
            {
                bool isSelected = (selectedIndex == i);
                if (ImGui::Selectable(sceneObjects[i].name.c_str(), isSelected))
                    selectedIndex = i;
            }

            ImGui::Separator();


            if (selectedIndex >= 0 && selectedIndex < (int)sceneObjects.size())
            {
                SceneObject &sel = sceneObjects[selectedIndex];

                ImGui::Text("Properties: %s", sel.name.c_str());
                ImGui::DragFloat3("Position", &sel.position.x, 0.05f, -20.0f, 20.0f);
                ImGui::DragFloat3("Rotation", &sel.rotation.x, 1.0f, -180.0f, 180.0f);
                ImGui::DragFloat3("Scale", &sel.scale.x, 0.05f, 0.01f, 10.0f);
                ImGui::ColorEdit3("Color", &sel.color.x);
            }

            ImGui::Separator();
            ImGui::TextDisabled(Globals::cameraControlEnabled
                ? "Camera ativa (solte o botao direito para usar a UI)"
                : "UI ativa (segure o botao direito para mover a camera)");

            ImGui::End();



            for (auto &obj : sceneObjects)
            {
                obj.shader->useShaders();
                obj.shader->setMat4("projection", projection);
                obj.shader->setMat4("view", view);
                obj.shader->setMat4("model", obj.GetModelMatrix());
                obj.shader->setVec3("uColor", obj.color);

                obj.shape->desenharElem();
            }




            ImGuiOverlay::End();

            // Troca buffers e trata eventos
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete cubeSH;
        delete mesh;
    }

    ImGuiOverlay::Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}