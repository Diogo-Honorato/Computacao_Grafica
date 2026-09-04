#pragma once

#include "imgui.h"
#include "SceneObject.hpp"
#include "Scene.hpp"
#include <fstream>
#include <iostream>
#include <concepts>
#include <filesystem>
#include "../dep/json/json.hpp"
#include "ImGuizmo.h"


    NLOHMANN_JSON_SERIALIZE_ENUM(PrimitiveTypeObj, {
        {PrimitiveTypeObj::Cube,       "Cube"},
        {PrimitiveTypeObj::Sphere,     "Sphere"},
        {PrimitiveTypeObj::Circle,     "Circle"},
        {PrimitiveTypeObj::Triangle,   "Triangle"},
        {PrimitiveTypeObj::Square,     "Square"},
        {PrimitiveTypeObj::Cylinder,   "Cylinder"},
        {PrimitiveTypeObj::Paraboloid, "Paraboloid"},
    })

namespace Gui{

    namespace Menu{

        using json = nlohmann::json;


        enum class TypeButton {
            PROJECT, NEW, OPEN, EXPORT, SAVE, DELETE,

            OBJECT, ADD_OBJ, TEX, LOAD_FOLDER_TEX, LOAD_FILE_TEX,  LOAD_FOLDER_OBJ,  LOAD_FILE_OBJ,

            SCENE, LIGHT, GRID, METRICS,

            CAM, GIZMO_CAM, POS_FIRST, UNKNOWN
        };


        NLOHMANN_JSON_SERIALIZE_ENUM(TypeButton, {
            {TypeButton::UNKNOWN,         "UNKNOWN"},
            {TypeButton::PROJECT,         "PROJECT"},
            {TypeButton::NEW,             "NEW"},
            {TypeButton::OPEN,            "OPEN"},
            {TypeButton::EXPORT,          "EXPORT"},
            {TypeButton::SAVE,            "SAVE"},
            {TypeButton::DELETE,          "DELETE"},
            {TypeButton::OBJECT,          "OBJECT"},
            {TypeButton::ADD_OBJ,         "ADD_OBJ"},
            {TypeButton::TEX,             "TEX"},
            {TypeButton::LOAD_FOLDER_TEX, "LOAD_FOLDER_TEX"},
            {TypeButton::LOAD_FILE_TEX,   "LOAD_FILE_TEX"},
            {TypeButton::LOAD_FOLDER_OBJ, "LOAD_FOLDER_OBJ"},
            {TypeButton::LOAD_FILE_OBJ,   "LOAD_FILE_OBJ"},
            {TypeButton::SCENE,           "SCENE"},
            {TypeButton::LIGHT,           "LIGHT"},
            {TypeButton::GRID,            "GRID"},
            {TypeButton::METRICS,         "METRICS"},
            {TypeButton::CAM,             "CAM"},
            {TypeButton::GIZMO_CAM,       "GIZMO_CAM"},
            {TypeButton::POS_FIRST,       "POS_FIRST"}
        })





        struct Button {
            std::string label;
            TypeButton type;
            bool toggle = false;

            PrimitiveTypeObj primitiveType = PrimitiveTypeObj::Cube;

            std::vector<Button> subButton;
        };


        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Button, label, type, toggle, primitiveType, subButton)



        bool compareButton(const Button& btt, TypeButton key);
        bool compareButton(const Button& btt, PrimitiveTypeObj key);

        template <typename T>
        requires std::is_enum_v<T>
        const Button* findButtonRecursive(const std::vector<Button>& buttons,T enumKey) {
            for (const auto& btt : buttons) {
                
                if (compareButton(btt,enumKey)) {
                    return &btt;
                }
                
                if (!btt.subButton.empty()) {
                    const Button* key = findButtonRecursive(btt.subButton, enumKey);
                    if (key != nullptr) return key;
                }
            }
            return nullptr;
        }


        class MenuButton
        {
        public:
        
            bool loadFromFile(const std::string& path);
            
            template <typename T>
            requires std::is_enum_v<T>
            const Button* findButton(T enumKey) {
        
                return findButtonRecursive(root, enumKey);
            }

            void renderMenu(Scene &scene);

        private:
            std::vector<Button> root;
            Button* render();
            Button* renderRecursive(std::vector<Button>& buttons);
        };


        namespace Panel{

            enum class TextureSlot { 
                None, 
                Diffuse, 
                Specular 
            };


            void hierarchyConfig(Scene &scene);
            void sceneConfig(Scene &scene);
            void propertiesConfig(Scene &scene);


            std::vector<std::string> listTexture(const std::string &pathTex);
            inline std::vector<Button> subButtonAdd;
            inline TextureSlot pendingSlot = TextureSlot::None;
            inline std::string DEFAULT_DIRECTORY_TEXTURE =  "../texture/";


        }

    }


    namespace Guizmo{

        struct Render{
            bool guizmoTranslate = true;
            bool guizmoRotation = false;
            bool guizmoScale = false;
            ImGuizmo::OPERATION operation = ImGuizmo::TRANSLATE;
            ImGuizmo::MODE mode = ImGuizmo::LOCAL;
        };

        inline Guizmo::Render render;

        void drawGuizmo(Scene &scene, glm::mat4 &projection, glm::mat4 &view);
    }
}