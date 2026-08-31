#include "../include/Menu.hpp"

namespace Menu
{

    bool MenuButton::loadFromFile(const std::string &path)
    {
        std::ifstream arquivo(path);
        if (!arquivo.is_open())
        {
            std::cerr << "[MenuButton] Erro ao abrir arquivo: " << path << std::endl;
            return false;
        }

        try
        {
            json jData;
            arquivo >> jData;

            root = jData.get<std::vector<Button>>();

            arquivo.close();
            return true;
        }
        catch (json::parse_error &e)
        {
            std::cerr << "[MenuButton] Erro de sintaxe no JSON: " << e.what() << std::endl;
            return false;
        }
    }

    Button *MenuButton::render()
    {
        return renderRecursive(root);
    }

    Button *MenuButton::renderRecursive(std::vector<Button> &buttons)
    {

        Button *clicked = nullptr;

        for (auto &botao : buttons)
        {
            if (!botao.subButton.empty())
            {
                if (ImGui::BeginMenu(botao.label.c_str()))
                {

                    Button *nested = renderRecursive(botao.subButton);
                    if (nested)
                        clicked = nested;

                    ImGui::EndMenu();
                }
            }
            else
            {
                if (ImGui::MenuItem(botao.label.c_str(), nullptr, &botao.toggle))
                    clicked = &botao;
            }
        }

        return clicked;
    }

    void MenuButton::renderMenu(Scene &scene)
    {

        float menuBarHeight = 0.0f;

        if (ImGui::BeginMainMenuBar())
        {
            menuBarHeight = ImGui::GetFrameHeight();

            Button *actionBtt = render();

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
                    scene.selectedIndex = (int)scene.GetObjects().size() - 1;
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
    }

    bool compareButton(const Button &btt, TypeButton key)
    {

        return btt.type == key;
    }

    bool compareButton(const Button &btt, PrimitiveTypeObj key)
    {

        return btt.primitiveType == key;
    }


    namespace Panel
    {
        void hierarchyConfig(Scene &scene){

            auto &objects = scene.GetObjects();

            // PAINEL HIERARCHY
            ImGui::Begin("Hierarchy");

            for (int i = 0; i < (int)objects.size(); i++)
            {
                bool isSelected = (scene.selectedIndex == i);
                if (ImGui::Selectable(objects[i].name.c_str(), isSelected))
                    scene.selectedIndex = i;
            }

            ImGui::End();

        }

        void sceneConfig(Scene &scene){

            if (scene.lightingEnabled)
            {
                ImGui::Begin("Scene Settings");

                ImGui::Text("Light");
                ImGui::DragFloat3("Light Position", &scene.light.position.x, 0.05f, -20.0f, 20.0f);
                ImGui::ColorEdit3("Light Ambient", &scene.light.ambient.x);
                ImGui::ColorEdit3("Light Diffuse", &scene.light.diffuse.x);
                ImGui::ColorEdit3("Light Specular", &scene.light.specular.x);

                ImGui::End();
            }
        }

        void propertiesConfig(Scene &scene,Texture *placeholderDiffuse,Texture *placeholderSpecular){

            if (scene.selectedIndex >= 0 && scene.selectedIndex < (int)scene.GetObjects().size())
            {
                SceneObject &sel = scene.GetObjects()[scene.selectedIndex];

                ImGui::Begin("Properties");

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
                    scene.RemoveObject(scene.selectedIndex);
                    scene.selectedIndex = -1;

                }

                ImGui::End();

            }

        }
    } 
    
}