#include "../include/Menu.hpp"

namespace Menu {

    bool MenuButton::LoadFromFile(const std::string& path)
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
        catch (json::parse_error& e)
        {
            std::cerr << "[MenuButton] Erro de sintaxe no JSON: " << e.what() << std::endl;
            return false;
        }
    }

    Button* MenuButton::Render()
    {
        return RenderRecursive(root);
    }

    Button* MenuButton::RenderRecursive(std::vector<Button>& buttons)
    {
        
        Button* clicked = nullptr;

        for (auto& botao : buttons)
        {
            if (!botao.subButton.empty())
            {
                if (ImGui::BeginMenu(botao.label.c_str()))
                {
                    
                    Button* nested = RenderRecursive(botao.subButton);
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

    bool compareButton(const Button& btt, TypeButton key){

        return btt.type == key;
    }

    bool compareButton(const Button& btt, PrimitiveTypeObj key){

        return btt.primitiveType == key;
    }
}