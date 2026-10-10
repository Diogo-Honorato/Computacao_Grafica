#pragma once

#include "imgui.h"
#include "SceneObject.hpp"
#include "Project.hpp"
#include "Scene.hpp"
#include "ImGuizmo.h"
#include "../dep/imgui/misc/cpp/imgui_stdlib.h"
#include "Window.hpp"
#include <iostream>
#include <concepts>
#include <nfd.h>
#include <thread>
#include <atomic>
#include <mutex>



    NLOHMANN_JSON_SERIALIZE_ENUM(PrimitiveTypeObj, {
        {PrimitiveTypeObj::Cube,       "Cube"},
        {PrimitiveTypeObj::Sphere,     "Sphere"},
        {PrimitiveTypeObj::Circle,     "Circle"},
        {PrimitiveTypeObj::Triangle,   "Triangle"},
        {PrimitiveTypeObj::Square,     "Square"},
        {PrimitiveTypeObj::Cylinder,   "Cylinder"},
        {PrimitiveTypeObj::Paraboloid, "Paraboloid"},
        {PrimitiveTypeObj::Grid,       "Grid"},
        {PrimitiveTypeObj::TileGrid,   "TileGrid"},
    })

namespace Gui{

    namespace Menu{

        using json = nlohmann::json;


        enum class TypeButton {
            PROJECT, NEW_PROJECT, OPEN_PROJECT, LOAD_SCENE, SAVE_PROJECT,

            OBJECT, ADD_OBJ, LOAD_FILE_OBJ,

            SCENE, LIGHT, METRICS,

            CAM, GIZMO_CAM, POS_FIRST, UNKNOWN
        };


        NLOHMANN_JSON_SERIALIZE_ENUM(TypeButton, {
            {TypeButton::UNKNOWN,         "UNKNOWN"},
            {TypeButton::PROJECT,         "PROJECT"},
            {TypeButton::NEW_PROJECT,     "NEW_PROJECT"},
            {TypeButton::OPEN_PROJECT,    "OPEN_PROJECT"},
            {TypeButton::LOAD_SCENE,      "LOAD_SCENE"},
            {TypeButton::SAVE_PROJECT,    "SAVE_PROJECT"},
            {TypeButton::OBJECT,          "OBJECT"},
            {TypeButton::ADD_OBJ,         "ADD_OBJ"},
            {TypeButton::LOAD_FILE_OBJ,   "LOAD_FILE_OBJ"},
            {TypeButton::SCENE,           "SCENE"},
            {TypeButton::LIGHT,           "LIGHT"},
            {TypeButton::METRICS,         "METRICS"},
            {TypeButton::CAM,             "CAM"},
            {TypeButton::GIZMO_CAM,       "GIZMO_CAM"},
            {TypeButton::POS_FIRST,       "POS_FIRST"},
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

            void renderMenu(Project &proj);

        private:
            std::vector<Button> root;
            Button* render();
            Button* renderRecursive(std::vector<Button>& buttons);
        };


        namespace Panel{

            struct AsyncTexture
            {
                std::atomic<bool> inProgress = false;
                std::mutex mutex;
                std::string pendingPath;
                bool hasPending = false;
            };

            inline AsyncTexture diffuseAsync;
            inline AsyncTexture specularAsync;
            inline bool isOpenNewProject = false;
            inline bool isOpenLoadProject = false;
            inline bool isOpenLoadScene = false;
            inline bool isOpenExitConfirm =false;
            inline bool isFirstOpenLoadProject = true;
            inline bool isFirstOpenNewProject = true;
            inline bool isOpenPopupSave = false;
            inline double popupSaveOpenTime = 0.0;


            
            void requestTextureAsync(AsyncTexture& asyncTex, const std::string& initialDir);
            bool capturingTexture(AsyncTexture& asyncTex, std::string& outPath);

            void hierarchyConfig(Scene &scene);
            void sceneConfig(Project &proj);
            void propertiesConfig(Project &proj);
            
            void showMetrics(Scene &scene);
            void newProject(Project &proj,Shader *uberSH);
            void loadProject(Project &proj, Shader *uberSH);
            void loadScene(Project &proj, Shader *uberSH);
            void exitConfirm(Project& proj, GLFWwindow* window);

            void buttonReturnNewProject();
            void newProjectWindow(Project &proj, Shader *uberSH);
            void loadProjectWindow(Project &proj, Shader *uberSH);
            void loadSceneWindow(Project &proj, Shader *uberSH);
            void exitConfirmWindow(Project& proj, GLFWwindow* window);
            void savePopup();

            
            nfdchar_t* openFileDialog(const std::string &pathDir);
            std::string openFolderDialog(const std::string& pathDir);
            void drawThumbnail(const char* label, Texture* tex, const std::string& path);
            inline std::vector<Button> subButtonAdd;



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

    namespace MousePicking{

        inline GLuint pickingFBO;

        void setupFrameBufferPicking(int &windowWidth ,int &windowHeight);
        int objectPicking (int mouseX, int mouseY, int windowHeight,std::vector<SceneObject>& objects, Shader* pickingMouseShader,const glm::mat4& projection, const glm::mat4& view);
    }
}