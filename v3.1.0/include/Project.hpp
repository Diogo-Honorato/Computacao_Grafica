#pragma once

#include <filesystem>
#include <system_error>
#include <fstream>
#include "Scene.hpp"

using json = nlohmann::json;

class Project
{
private:
    std::string pathLocal;
    std::string nameProj;
    std::string pathProject;
    std::string currentSceneName;
    bool wasSaved = true;
    std::unordered_map<std::string,std::string> pathScenes;
    std::unordered_map<std::string, Scene*> loadedScenes;
    
public:

    Project(const std::string &pathLocal, const std::string &nameProj);
    Project &operator=(const Project &proj); 
    Project() = default;
    ~Project();

    bool createSceneDir(const std::string &nameScene);
    std::string getScenePath(const std::string& nameScene) const;
    Scene* createScene(const std::string& nameScene, Shader* defaultShader);
    Scene& loadScene(const std::string& nameScene, Shader* defaultShader);
    Scene& getCurrentScene();
    void setCurrentScene(const std::string& nameScene);
    bool isSceneLoaded(const std::string& nameScene) const;
    bool saveProject();
    bool loadProject(const std::string& configFilePath, Shader* defaultShader);


    void markDirty() { wasSaved = false; }
    const std::string& getPathLocal() const { return pathLocal; }
    const std::string& getNameProj() const { return nameProj; }
    const std::string& getPathProject() const { return pathProject; }
    const std::string& getCurrentSceneName() const { return currentSceneName; }
    const std::unordered_map<std::string, std::string>& getPathScenes() const { return pathScenes; }
    bool getWasSaved() const { return wasSaved; }

    
    static inline void saveLastProjectPath(const std::string& projectFilePath){

        std::ofstream file(INIT_FILE_PATH);

        if (file.is_open())

            file << projectFilePath;
    }

    static inline std::string loadProjectInit(){

        std::ifstream file(INIT_FILE_PATH);

        if (!file.is_open())
            return "";

        std::string path;

        std::getline(file, path);

        if (path.empty() || !std::filesystem::exists(path))
            return "";

        return path;
    }


    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Project, pathLocal, nameProj, pathProject, pathScenes, currentSceneName, wasSaved)
};