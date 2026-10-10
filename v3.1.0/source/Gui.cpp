#include "../include/Gui.hpp"

namespace Gui
{
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

        void MenuButton::renderMenu(Project &proj)
        {

            float menuBarHeight = 0.0f;

            if (ImGui::BeginMainMenuBar())
            {
                menuBarHeight = ImGui::GetFrameHeight();

                Button *actionBtt = render();

                auto &scene = proj.getCurrentScene();

                if (actionBtt != nullptr)
                {
                    switch (actionBtt->type)
                    {

                    case Menu::TypeButton::NEW_PROJECT:

                        proj.saveProject();
                        Gui::Menu::Panel::isOpenPopupSave = true;
                        Gui::Menu::Panel::isOpenNewProject = actionBtt->toggle;
                        
                        break;

                    case Menu::TypeButton::OPEN_PROJECT:
                        proj.saveProject();
                        Gui::Menu::Panel::isOpenPopupSave = true;
                        Gui::Menu::Panel::isOpenLoadProject = actionBtt->toggle;
                        
                        break;

                    case Menu::TypeButton::LOAD_SCENE:
                        
                        proj.saveProject();
                        Gui::Menu::Panel::isOpenLoadScene = actionBtt->toggle;
                        break;

                    case Menu::TypeButton::SAVE_PROJECT:
                        proj.saveProject();
                        Gui::Menu::Panel::isOpenPopupSave = true;
                        Gui::Menu::Panel::popupSaveOpenTime = ImGui::GetTime();
                        
                        break;

                    case Menu::TypeButton::LOAD_FILE_OBJ:
                        break;

                    case Menu::TypeButton::ADD_OBJ:

                        scene.AddObject(actionBtt->primitiveType, DEFAULT_DIFFUSE_TEXTURE, DEFAULT_SPECULAR_TEXTURE);
                        scene.selectedIndex = (int)scene.GetObjects().size() - 1;
                        proj.markDirty();
                        break;

                    case Menu::TypeButton::LIGHT:

                        scene.lightingEnabled = actionBtt->toggle;
                        proj.markDirty();
                        break;

                    case Menu::TypeButton::METRICS:
                        scene.showMetrics = actionBtt->toggle;
                        break;

                    case Menu::TypeButton::GIZMO_CAM:
                        break;

                    case Menu::TypeButton::POS_FIRST:
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
            void hierarchyConfig(Scene &scene)
            {

                auto &objects = scene.GetObjects();

                // PAINEL HIERARCHY
                ImGui::Begin("HIERARCHY");

                for (int i = 0; i < (int)objects.size(); i++)
                {
                    bool isSelected = (scene.selectedIndex == i);
                    if (ImGui::Selectable(objects[i].name.c_str(), isSelected))
                        scene.selectedIndex = i;
                }

                ImGui::End();
            }

            void sceneConfig(Project &proj)
            {

                auto &scene = proj.getCurrentScene();

                ImGui::Begin("SCENE SETTINGS");

                bool anyChanged = false;

                if (scene.lightingEnabled)
                {

                    ImGui::Text("Light");
                    anyChanged |=ImGui::DragFloat3("Light Position", &scene.light.position.x, 0.05f, -20.0f, 20.0f);
                    anyChanged |=ImGui::ColorEdit3("Light Ambient", &scene.light.ambient.x);
                    anyChanged |=ImGui::ColorEdit3("Light Diffuse", &scene.light.diffuse.x);
                    anyChanged |=ImGui::ColorEdit3("Light Specular", &scene.light.specular.x);
                }

                ImGui::Separator();

                ImGui::Text("Objects");

                if (ImGui::Button("Add Object"))
                {

                    ImGui::OpenPopup("Object List");
                }

                if (ImGui::BeginPopup("Object List"))
                {

                    for (auto &btt : Menu::Panel::subButtonAdd)
                    {

                        if (ImGui::Selectable(btt.label.c_str()))
                        {

                            scene.AddObject(btt.primitiveType, DEFAULT_DIFFUSE_TEXTURE, DEFAULT_SPECULAR_TEXTURE);
                            scene.selectedIndex = (int)scene.GetObjects().size() - 1;
                            anyChanged = true;
                        }
                    }

                    ImGui::EndPopup();
                }

                ImGui::SameLine();

                if (ImGui::Button("Remove Object"))
                {
                    scene.RemoveObject(scene.selectedIndex);
                    scene.selectedIndex = -1;
                    anyChanged = true;
                }

                ImGui::SameLine();

                if (ImGui::Button("Copy Object") && scene.selectedIndex >= 0)
                {
                    scene.CopyObject(scene.GetObjects()[scene.selectedIndex]);
                    scene.selectedIndex = (int)scene.GetObjects().size() - 1;
                    anyChanged = true;
                }

                if (ImGui::Button("Object Modeling"))
                {
                    //object modeling
                }


                ImGui::End();

                if(anyChanged){
                    proj.markDirty();
                }
            }

            void propertiesConfig(Project &proj)
            {
                auto &scene = proj.getCurrentScene();

                if (scene.selectedIndex >= 0 && scene.selectedIndex < (int)scene.GetObjects().size())
                {
                    SceneObject &sel = scene.GetObjects()[scene.selectedIndex];

                    bool anyChanged = false;

                    ImGui::Begin("PROPERTIES");

                    ImGui::Text("%s", sel.name.c_str());

                    ImGui::Separator();

                    //Guizmo options
                    ImGui::Checkbox("Translate", &Guizmo::render.guizmoTranslate);
                    ImGui::SameLine();
                    ImGui::Checkbox("Rotate", &Guizmo::render.guizmoRotation);
                    ImGui::SameLine();
                    ImGui::Checkbox("Scale", &Guizmo::render.guizmoScale);

                    ImGui::Separator();

                    // Transform
                    anyChanged |=ImGui::DragFloat3("Traslate", &sel.position.x, 0.05f, -20.0f, 20.0f);

                    glm::vec3 eulerDegrees = glm::degrees(glm::eulerAngles(sel.rotation));
                    
                    if(ImGui::DragFloat3("Rotation", &eulerDegrees.x, 1.0f))
                        sel.rotation = glm::quat(glm::radians(eulerDegrees));
                        anyChanged = true;

                    anyChanged |=ImGui::DragFloat3("Scale", &sel.scale.x, 0.05f, 0.01f, 10.0f);

                    ImGui::Separator();

                    ImGui::RadioButton("Local", (int*)&Guizmo::render.mode,ImGuizmo::MODE::LOCAL);
                    ImGui::SameLine();
                    ImGui::RadioButton("World", (int*)&Guizmo::render.mode,ImGuizmo::MODE::WORLD);

                    ImGui::Separator();

                    // Cores do Material
                    ImGui::Text("Material");
                    anyChanged |=ImGui::ColorEdit3("Color (Diffuse)", &sel.color.x);
                    anyChanged |=ImGui::ColorEdit3("Ambient", &sel.ambient.x);
                    anyChanged |=ImGui::ColorEdit3("Specular", &sel.specular.x);
                    anyChanged |=ImGui::DragFloat("Shininess", &sel.shininess, 1.0f, 1.0f, 256.0f);

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

                    case PrimitiveTypeObj::Grid:
                        ImGui::Separator();
                        ImGui::Text("Grid Dimensions");
                        geometryChanged |= ImGui::SliderInt("Lines",&sel.linesGrid,1, 50);
                        geometryChanged |= ImGui::SliderInt("Columns",&sel.columnsGrid,1, 50);
                        break;

                    case PrimitiveTypeObj::Cube:
                    case PrimitiveTypeObj::Triangle:
                    case PrimitiveTypeObj::Square:
                        break;
                    }

                    anyChanged |=geometryChanged;

                    if (geometryChanged)
                        scene.RegenerateMesh(sel);

                    ImGui::Separator();

                    
                    // Texture
                    ImGui::Text("Texture");

                    if (ImGui::Button("Choose Diffuse "))
                    {
                        requestTextureAsync(diffuseAsync,scene.textureDir);
                    }

                    ImGui::SameLine();
                    if (ImGui::Button("Remove Diffuse "))
                    {
                        sel.diffuseTex = scene.getTexture(DEFAULT_DIFFUSE_TEXTURE);
                        sel.nameDiffTexture = DEFAULT_DIFFUSE_TEXTURE;
                        anyChanged = true;
                    }  
                    
                    if(capturingTexture(diffuseAsync,sel.diffuseTexPathKey)){

                        sel.nameDiffTexture = scene.importTexture(sel.diffuseTexPathKey);

                        sel.diffuseTex = scene.getTexture(sel.nameDiffTexture);
                        
                        sel.diffuseTexPathKey.clear();

                        anyChanged = true;
                    }

                    drawThumbnail("diffuse texture",sel.diffuseTex,sel.nameDiffTexture);

                    if (ImGui::Button("Choose Specular"))
                    {
                        requestTextureAsync(specularAsync,scene.textureDir);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Remove Specular"))
                    {
                        sel.specularTex = scene.getTexture(DEFAULT_SPECULAR_TEXTURE);
                        sel.nameSpecTexture = DEFAULT_SPECULAR_TEXTURE;
                        anyChanged = true;
                    }

                    if(capturingTexture(specularAsync,sel.specularTexPathKey)){

                        sel.nameSpecTexture = scene.importTexture(sel.specularTexPathKey);

                        sel.specularTex = scene.getTexture(sel.nameSpecTexture);

                        sel.specularTexPathKey.clear();

                        anyChanged = true;
                    }

                    drawThumbnail("specular texture",sel.specularTex,sel.nameSpecTexture);
                    
                                 
                    ImGui::End();

                    if(anyChanged){

                        proj.markDirty();
                    }
                }
            }



            void showMetrics(Scene &scene){

                if(scene.showMetrics){
                    
                    ImGui::ShowMetricsWindow(&scene.showMetrics);

                }
            }

            void newProject(Project &proj,Shader *uberSH){

                if(isOpenNewProject){

                    newProjectWindow(proj,uberSH);
                }
                else if(!isOpenNewProject && isFirstOpenNewProject){

                    buttonReturnNewProject();
                    
                }
            }

            void loadProject(Project &proj, Shader *uberSH){

                if(isOpenLoadProject){

                    loadProjectWindow(proj,uberSH);
                }
            }

            void loadScene(Project &proj, Shader *uberSH){

                if(isOpenLoadScene){

                    loadSceneWindow(proj,uberSH);
                }
            }

            void exitConfirm(Project& proj, GLFWwindow* window){

                if(isOpenExitConfirm){

                    exitConfirmWindow(proj,window);
                }
            }



            void buttonReturnNewProject(){

                ImVec2 screenSize = ImGui::GetIO().DisplaySize;

                ImVec2 windowSize = ImVec2(285.0f, 60.0f); 

                ImVec2 windowPos;
                windowPos.x = (screenSize.x - windowSize.x) * 0.5f;
                windowPos.y = (screenSize.y - windowSize.y) * 0.5f;

                ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

                ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

                if (ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)){

                    ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - 240.0f) * 0.75f);

                    ImGui::SetCursorPosY((ImGui::GetContentRegionAvail().y - 40.0f) * 2.45f);

                    ImGui::SetWindowFontScale(1.5f);

                    if (ImGui::Button("+ NEW PROJECT", ImVec2(240, 40)))
                    {
                        isOpenNewProject = true;
                    }
                    
                    ImGui::SetWindowFontScale(1.0f);
                }
                ImGui::End();
            }
            
            void newProjectWindow(Project &proj, Shader *uberSH)
            {
                ImGui::SetNextWindowSize(ImVec2(520, 360), ImGuiCond_FirstUseEver);
            
                if (ImGui::Begin("Create New Project", nullptr, ImGuiWindowFlags_NoCollapse ))
                {
                    static std::string nameProj = "";
                    static std::string pathDirectory = std::filesystem::path(getenv(HOME_VAR)).string();
                    static std::string firstNameScene = "MainScene";
                    static std::string errorMessage = "";
                    static std::string labelPath = "";
                
                    ImGui::Text("Name Project:");
                    ImGui::InputText("##NameProject", &nameProj);
                    
                    if (ImGui::Button("Load Project", ImVec2(240, 0)))
                    {
                        isOpenNewProject = false;
                        isOpenLoadProject = true;
                    }
                
                    ImGui::Spacing();
                
                    ImGui::Text("Browse: ");
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 110.0f);
                    labelPath = (std::filesystem::path(pathDirectory) / nameProj);
                    ImGui::InputText("##Path", &labelPath);
                    ImGui::PopItemWidth();
                
                    ImGui::SameLine();
                
                    if (ImGui::Button("Search", ImVec2(100, 0)))
                    {
                        std::string pickDir = openFolderDialog(pathDirectory);
                        if (!pickDir.empty())
                            pathDirectory = pickDir;
                    }
                
                    ImGui::Spacing();
                
                    ImGui::Text("Name Current Scene:");
                    ImGui::InputText("##Scene", &firstNameScene);
                
                    ImGui::Spacing();
                
                    if (!errorMessage.empty())
                    {
                        ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f), "%s", errorMessage.c_str());
                        ImGui::Spacing();
                    }
                
                    ImGui::Separator();
                    ImGui::Spacing();
                
                    bool canCreate = !nameProj.empty() && !pathDirectory.empty() && !firstNameScene.empty();
                
                    float availWidth = ImGui::GetContentRegionAvail().x;
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + availWidth - 200.0f);
                    

                    if (ImGui::Button("Cancel", ImVec2(90, 0)))
                    {
                        errorMessage = "";
                        if (isOpenNewProject) isOpenNewProject = false;
                    }
                
                    ImGui::SameLine();
                
                    ImGui::BeginDisabled(!canCreate);

                    if (ImGui::Button("Ok", ImVec2(90, 0)))
                    {
                        proj = Project(pathDirectory, nameProj);
                    
                        if (proj.createScene(firstNameScene, uberSH) != nullptr)
                        {
                            errorMessage = "";
                            nameProj = "";
                            firstNameScene = "MainScene";
                            labelPath = "";
                            std::string projectCfg = (std::filesystem::path(proj.getPathProject()) / "project.cfg").string();
                            Project::saveLastProjectPath(projectCfg);
                            proj.markDirty();

                            if (isOpenNewProject) {
                                isOpenNewProject = false; 
                                isFirstOpenNewProject = false;
                            }
                            
                        }
                        else
                        {
                            errorMessage = "Failed to create the project. Check if the path is valid and if you have write permission there.";
                        }
                    }
                    ImGui::EndDisabled();
                }
                ImGui::End();
            }               

            void loadProjectWindow(Project &proj, Shader *uberSH)
            {
                ImGui::SetNextWindowSize(ImVec2(420, 150), ImGuiCond_FirstUseEver);

                if (ImGui::Begin("Load Project", &isOpenLoadProject, ImGuiWindowFlags_NoCollapse))
                {
                    static std::string errorMessage = "";

                    ImGui::Text("Select the project folder:");
                    ImGui::Spacing();

                    if (ImGui::Button("Browse", ImVec2(120, 0)))
                    {
                        static std::string pathDirectory = std::filesystem::path(getenv(HOME_VAR)).string();

                        std::string selectedDir = openFolderDialog(pathDirectory);

                        if (!selectedDir.empty())
                        {
                            std::filesystem::path cfgPath = std::filesystem::path(selectedDir) / "project.cfg";

                            if (std::filesystem::exists(cfgPath))
                            {
                                if (proj.loadProject(cfgPath.string(), uberSH))
                                {
                                    errorMessage = "";
                                    isOpenLoadProject = false;
                                    Project::saveLastProjectPath(cfgPath.string());
                                }
                                else
                                {
                                    errorMessage = "The project.cfg file exists, but could not be read (invalid format?).";
                                }
                            }
                            else
                            {
                                errorMessage = "This folder does not contain a valid project (project.cfg not found).";
                            }
                        }
                    }

                    if (!errorMessage.empty())
                    {
                        ImGui::Spacing();
                        ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f), "%s", errorMessage.c_str());
                    }
                }
                ImGui::End();
            }

            void loadSceneWindow(Project &proj, Shader *uberSH)
            {
                ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

                if (ImGui::Begin("Load Scene", &isOpenLoadScene, ImGuiWindowFlags_NoCollapse))
                {
                    for (auto& [sceneName, scenePath] : proj.getPathScenes())
                    {
                        bool isCurrent = (sceneName == proj.getCurrentSceneName());

                        if (ImGui::Selectable(sceneName.c_str(), isCurrent))
                        {
                            proj.loadScene(sceneName, uberSH);
                            proj.setCurrentScene(sceneName);
                            isOpenLoadScene = false;
                        }
                    }
                }
                ImGui::End();
                
            }

            void exitConfirmWindow(Project& proj, GLFWwindow* window)
            {
                if (!isOpenExitConfirm) return;

                ImGui::OpenPopup("Exit without saving?");

                if (ImGui::BeginPopupModal("Exit without saving?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ImGui::Text("You have unsaved changes in the current project.");
                    ImGui::Spacing();

                    if (ImGui::Button("Exit and saving", ImVec2(130, 0)))
                    {
                        proj.saveProject();
                        isOpenExitConfirm = false;
                        ImGui::CloseCurrentPopup();
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Exit without saving", ImVec2(150, 0)))
                    {
                        isOpenExitConfirm = false;
                        ImGui::CloseCurrentPopup();
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Cancel", ImVec2(100, 0)))
                    {
                        isOpenExitConfirm = false;
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }
            }
            
            void savePopup(){

                if (isOpenPopupSave) {
                
                    ImGuiViewport* viewport = ImGui::GetMainViewport();
                    ImVec2 posWindow = ImVec2(viewport->Pos.x, viewport->Pos.y + 80);

                    ImGui::SetNextWindowPos(posWindow, ImGuiCond_Always);

                    ImGui::SetNextWindowBgAlpha(0.85f);

                    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | 
                        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

                    if (ImGui::Begin("##Saved Notification", &isOpenPopupSave, flags)) {
                    
                        ImGui::Text("Project saved successfully!");
                    }

                    ImGui::End();

                    if (ImGui::GetTime() - popupSaveOpenTime > 2.0) {
                        isOpenPopupSave = false;
                    }
                }
            }


            nfdchar_t* openFileDialog(const std::string &pathDir)
            {

                nfdchar_t* outPath = nullptr;

                nfdfilteritem_t filters[1] = {{"Images", "png,jpeg"}};

                nfdresult_t result = NFD_OpenDialog(&outPath,filters,1,pathDir.c_str());

                if(result == NFD_ERROR){

                    std::cerr << "[NFD] Erro: " << NFD_GetError() << std::endl;
                    return nullptr;
                }

                return outPath;
            }
            
            std::string openFolderDialog(const std::string& pathDir)
            {
                nfdchar_t* outPath = nullptr;
                
                nfdresult_t result = NFD_PickFolder(&outPath, pathDir.c_str());

                if (result == NFD_OKAY)
                {
                    std::string selectedPath = outPath;
                    NFD_FreePath(outPath);
                    return selectedPath;
                }
                else if (result == NFD_ERROR)
                {
                    std::cerr << "[NFD] Erro: " << NFD_GetError() << std::endl;
                }

                return "";
            }

            void drawThumbnail(const char* label, Texture* tex, const std::string& path)
            {

                ImGui::Image((ImTextureID)(intptr_t)tex->getTexID(), ImVec2(48, 48),ImVec2(0, 1), ImVec2(1, 0));
                ImGui::SameLine();
                
                ImGui::BeginGroup();
                ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "%s", label);
                ImGui::Text("%s", path.c_str());
                ImGui::EndGroup();
            }
            
            void requestTextureAsync(AsyncTexture& asyncTex, const std::string& initialDir){

                if (asyncTex.inProgress) return;

                asyncTex.inProgress = true;

                std::thread([&asyncTex,initialDir](){

                    nfdchar_t* pathTex = openFileDialog(initialDir);

                    if(pathTex){

                        std::lock_guard<std::mutex> lock(asyncTex.mutex);
                        asyncTex.pendingPath = pathTex;
                        asyncTex.hasPending = true;
                        NFD_FreePath(pathTex);
                    }

                    asyncTex.inProgress = false;

                }).detach();
            }

            bool capturingTexture(AsyncTexture& asyncTex, std::string& outPath){

                std::lock_guard<std::mutex> lock(asyncTex.mutex);

                if(!asyncTex.hasPending) 
                    return false;

                outPath = asyncTex.pendingPath;
                asyncTex.hasPending = false;
                return true;
            }
        }

    }

    namespace Guizmo
    {
        
        void drawGuizmo(Scene &scene,glm::mat4 &projection, glm::mat4 &view){

            if (scene.selectedIndex >= 0 && scene.selectedIndex < (int)scene.GetObjects().size()){
                
                SceneObject &sel = scene.GetObjects()[scene.selectedIndex];
                
                ImGuizmo::SetOrthographic(false);

                ImGuizmo::BeginFrame();

                ImGuizmo::SetRect(0, 0, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
                
                glm::mat4 model = sel.GetModelMatrix();
                
                int operation = 0;
                if(render.guizmoTranslate)  operation |= static_cast<int>(ImGuizmo::TRANSLATE);

                if(render.guizmoRotation)   operation |= static_cast<int>(ImGuizmo::ROTATE);
                    
                if(render.guizmoScale)      operation |= static_cast<int>(ImGuizmo::SCALE);
                    
                render.operation = static_cast<ImGuizmo::OPERATION>(operation);

                glm::mat4 deltaMatrix;
                
                ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(projection),render.operation, render.mode, glm::value_ptr(model), glm::value_ptr(deltaMatrix));
                
                if(ImGuizmo::IsUsing()){
  
                    float translation[3], rotation[3], scale[3];
                    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model), translation, rotation, scale);

                    glm::mat3 rotationColumn = glm::mat3(deltaMatrix);

                    rotationColumn[0] = glm::normalize(rotationColumn[0]);
                    rotationColumn[1] = glm::normalize(rotationColumn[1]);
                    rotationColumn[2] = glm::normalize(rotationColumn[2]);

                    glm::quat deltaRotation = glm::quat_cast(rotationColumn);

                    sel.position = glm::vec3(translation[0], translation[1], translation[2]);
                    sel.rotation = glm::normalize(deltaRotation * sel.rotation);//Usando quaternion para evitar gimbal lock
                    sel.scale    = glm::vec3(scale[0], scale[1], scale[2]);
                }
            }

        }
        
    }
   
    namespace MousePicking{

        void setupFrameBufferPicking(int &windowWidth ,int &windowHeight){

            GLuint pickingTexture;
            GLuint pickingDepthRBO;

            glGenFramebuffers(1, &MousePicking::pickingFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, MousePicking::pickingFBO);

            glGenTextures(1, &pickingTexture);
            glBindTexture(GL_TEXTURE_2D, pickingTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);

            
            glGenRenderbuffers(1, &pickingDepthRBO);
            glBindRenderbuffer(GL_RENDERBUFFER, pickingDepthRBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, windowWidth, windowHeight);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pickingDepthRBO);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cerr << "[MousePicking] Framebuffer incompleto!" << std::endl;

            glBindFramebuffer(GL_FRAMEBUFFER, 0);//voltar para o frame buffer 0
        }

        int objectPicking(int mouseX, int mouseY, int windowHeight,std::vector<SceneObject>& objects, Shader* pickingMouseShader,const glm::mat4& projection, const glm::mat4& view){


            glBindFramebuffer(GL_FRAMEBUFFER, Gui::MousePicking::pickingFBO);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            pickingMouseShader->useShaders();
            pickingMouseShader->setMat4("projection", projection);
            pickingMouseShader->setMat4("view", view);
            
            for (int i = 0; i < (int)objects.size(); i++)
            {
            
                int id = i + 1;
                
                //16.777.216 objetos
                float r = (id & 0x000000FF) / 255.0f;
                float g = ((id & 0x0000FF00) >> 8) / 255.0f;
                float b = ((id & 0x00FF0000) >> 16) / 255.0f;

                pickingMouseShader->setVec3("idColor", glm::vec3(r, g, b));
                pickingMouseShader->setMat4("model", objects[i].GetModelMatrix());
                objects[i].shape->drawObject();
            }
            
            unsigned char pixel[3];
            glReadPixels(mouseX, windowHeight - mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            
            int pickedID = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);
            int pickedIndex = pickedID - 1;

            if (pickedIndex < 0 || pickedIndex >= (int)objects.size()){
                pickedIndex = -1;
            }
                
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            return pickedIndex;
        }

    }

}