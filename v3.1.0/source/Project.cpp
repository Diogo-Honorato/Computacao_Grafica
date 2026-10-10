#include "../include/Project.hpp"

Project::Project(const std::string &pathLocal, const std::string &nameProj): pathLocal(pathLocal), nameProj(nameProj), wasSaved(false)
{
    std::filesystem::path baseDir = std::filesystem::path(pathLocal) / nameProj;
    pathProject = baseDir.string();

}

Project& Project::operator=(const Project &proj){

    if(this == &proj){

        return *this;
    }
    

    for (auto& [path, scene] : this->loadedScenes){

        if(scene != nullptr){

            delete scene;
            scene = nullptr;
        }
        
    }

    this->loadedScenes.clear();

    this->pathLocal = proj.pathLocal;
    this->nameProj = proj.nameProj;
    this->pathProject = proj.pathProject;
    this->currentSceneName = proj.currentSceneName;
    this->wasSaved = true;
    this->pathScenes = proj.pathScenes;

    return *this;
}

Project::~Project()
{
    for (auto& [path, scene] : loadedScenes)
        delete scene;
}

std::string Project::getScenePath(const std::string& nameScene) const
{
    return (std::filesystem::path(pathProject) / nameScene).string();
}

bool Project::createSceneDir(const std::string &nameScene)
{
    std::error_code ec;

    if (pathScenes.find(nameScene) != pathScenes.end())
        return false;

    std::filesystem::path baseSceneDir    = std::filesystem::path(pathProject) / nameScene;
    std::filesystem::path sceneTextureDir = baseSceneDir / "Texture";
    std::filesystem::path sceneObjectsDir = baseSceneDir / "Objects";

    std::filesystem::create_directories(sceneTextureDir, ec);
    if (ec) throw std::filesystem::filesystem_error("Failed to create the directory ", sceneTextureDir, ec);

    std::filesystem::create_directories(sceneObjectsDir, ec);
    if (ec) throw std::filesystem::filesystem_error("Failed to create the directory ", sceneObjectsDir, ec);

    pathScenes[nameScene] = baseSceneDir.string();
    wasSaved = false;
    return true;
}

Scene* Project::createScene(const std::string& nameScene, Shader* defaultShader)
{
    if(createSceneDir(nameScene)){

        std::string scenePath = getScenePath(nameScene);

        Scene* scene = new Scene(defaultShader);
        scene->nameScene = nameScene;
        scene->textureDir = (std::filesystem::path(scenePath) / "Texture").string();

        loadedScenes[scenePath] = scene;
        currentSceneName = nameScene;
        return scene;
    }

    return nullptr;
}

Scene& Project::loadScene(const std::string& nameScene, Shader* defaultShader)
{
    std::string scenePath = getScenePath(nameScene);

    auto it = loadedScenes.find(scenePath);
    if (it != loadedScenes.end())
        return *it->second;

    Scene* scene = new Scene(defaultShader);
    scene->nameScene = nameScene;
    scene->textureDir = (std::filesystem::path(scenePath) / "Texture").string();

    std::filesystem::path sceneFile = std::filesystem::path(scenePath) / "scene.json";
    if (std::filesystem::exists(sceneFile))
        scene->loadScene(sceneFile.string());

    loadedScenes[scenePath] = scene;
    
    return *scene;
}

Scene& Project::getCurrentScene()
{
    std::string scenePath = getScenePath(currentSceneName);
    return *loadedScenes.at(scenePath);
}

void Project::setCurrentScene(const std::string& nameScene)
{
    if (pathScenes.find(nameScene) != pathScenes.end())
        currentSceneName = nameScene;
}

bool Project::isSceneLoaded(const std::string& nameScene) const
{
    return loadedScenes.find(getScenePath(nameScene)) != loadedScenes.end();
}

bool Project::saveProject()
{
    std::filesystem::path configPath = std::filesystem::path(pathProject) / "project.cfg";
    std::ofstream file(configPath);
    if (!file.is_open()) return false;

    wasSaved = true;
    json j = *this;
    file << j.dump(4);

    for (auto& [scenePath, scene] : loadedScenes)
    {
        std::filesystem::path sceneFile = std::filesystem::path(scenePath) / "scene.json";
        scene->saveScene(sceneFile.string());
    }

    return true;
}

bool Project::loadProject(const std::string& configFilePath,Shader* defaultShader)
{

    std::ifstream file(configFilePath);
    if (!file.is_open()) return false;

    json j;
    file >> j;
    
    *this = j.get<Project>();
    
    pathProject = std::filesystem::path(configFilePath).parent_path().string();

    for (auto& [name, oldPath] : pathScenes)
        pathScenes[name] = getScenePath(name);

    for (auto& [name, path] : pathScenes)
        loadScene(name, defaultShader);


    if (pathScenes.find(currentSceneName) == pathScenes.end() && !pathScenes.empty())
        currentSceneName = pathScenes.begin()->first;


    return true;
}
