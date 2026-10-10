#include "../include/Scene.hpp"

Scene::Scene(Shader* defaultShader) : defaultShader(defaultShader) {

    textureCache[DEFAULT_DIFFUSE_TEXTURE] = new Texture(255, 255, 255, 255);
    textureCache[DEFAULT_SPECULAR_TEXTURE] = new Texture(0, 0, 0, 255);
    light.cubeShape = GetPrimitiveShape(PrimitiveTypeObj::Cube);

}

Scene::~Scene()
{
    for (auto &obj : objects)
    {
        if (obj.ownedMesh != nullptr)
        {
            delete obj.shape;
            delete obj.ownedMesh;
        }
    }

    // Libera a geometria compartilhada do cache (um único delete por tipo).
    for (auto &pair : shapeCache) delete pair.second;
    for (auto &pair : meshCache)  delete pair.second;
    for (auto &pair : textureCache)  delete pair.second;

}

std::string Scene::TypeName(PrimitiveTypeObj type)
{
    switch (type)
    {
        case PrimitiveTypeObj::Cube:       return "Cube";
        case PrimitiveTypeObj::Sphere:     return "Sphere";
        case PrimitiveTypeObj::Circle:     return "Circle";
        case PrimitiveTypeObj::Triangle:   return "Triangle";
        case PrimitiveTypeObj::Square:     return "Square";
        case PrimitiveTypeObj::Cylinder:   return "Cylinder";
        case PrimitiveTypeObj::Paraboloid: return "Paraboloid";
        case PrimitiveTypeObj::Grid:       return "Grid";
    }
    return "Object";
}

Mesh* Scene::BuildMesh(const SceneObject& obj)
{

    switch (obj.type)
    {
        case PrimitiveTypeObj::Cube:
            return Mesh::cubeMesh(true, true);

        case PrimitiveTypeObj::Sphere:
            return Mesh::sphereMesh(true, true, obj.radius, obj.slices, obj.stacks);

        case PrimitiveTypeObj::Circle:
            
            return Mesh::circleMesh(true, true, obj.radius, obj.slices);

        case PrimitiveTypeObj::Triangle:
            return Mesh::triangleMesh(true, true);

        case PrimitiveTypeObj::Square:
            return Mesh::squareMesh(true, true);

        case PrimitiveTypeObj::Cylinder:
            return Mesh::axialExtruderMesh(true, true, obj.capBottom, obj.capTop,
                                            obj.baseRadius, obj.topRadius, obj.height,
                                            obj.slices, obj.stacks);

        case PrimitiveTypeObj::Paraboloid:
            return Mesh::paraboloidMesh(true, true, obj.capBottom, obj.capTop,
                                         obj.height, obj.radius, obj.slices, obj.stacks);

        case PrimitiveTypeObj::Grid:
                return Mesh::gridMesh(obj.linesGrid,obj.columnsGrid);
        
        case PrimitiveTypeObj::TileGrid:
            return Mesh::tileGridMesh(obj.linesGrid, obj.columnsGrid, obj.cellSize, obj.tilePerCellMode);

    }

    return Mesh::cubeMesh(true, true);
}

Shape* Scene::GetPrimitiveShape(PrimitiveTypeObj type)
{
    auto it = shapeCache.find(type);
    if (it != shapeCache.end())
        return it->second;

    // Usa um SceneObject temporário só para reaproveitar BuildMesh() com os
    // parâmetros padrão da struct (definidos no SceneObject.hpp).
    SceneObject defaults;
    defaults.type = type;

    Mesh* mesh = BuildMesh(defaults);
    Shape* shape = new Shape(mesh, mesh->drawMode,mesh->withTexture,mesh->withNormals);
    mesh->clearCPUData();

    meshCache[type] = mesh;
    shapeCache[type] = shape;
    return shape;
}

Texture* Scene::getTexture(std::string texturePath){

    bool isDefaultAsset = (texturePath == DEFAULT_DIFFUSE_TEXTURE || texturePath == DEFAULT_SPECULAR_TEXTURE);
    std::string fullPath = isDefaultAsset ? texturePath : (std::filesystem::path(textureDir) / texturePath).string();
    
    auto it = textureCache.find(fullPath);
    if(it != textureCache.end())
        return it->second;

    
    Texture* tex = new Texture(fullPath);
    textureCache[fullPath] = tex;
    
    return tex;
}

std::string Scene::importTexture(const std::string& sourceAbsPath)
{
    if (sourceAbsPath == DEFAULT_DIFFUSE_TEXTURE || sourceAbsPath == DEFAULT_SPECULAR_TEXTURE)
        return sourceAbsPath;
 
    std::string fileName = std::filesystem::path(sourceAbsPath).filename().string();
    std::filesystem::path destPath = std::filesystem::path(textureDir) / fileName;
 
    std::error_code ec;
    if (std::filesystem::absolute(sourceAbsPath) != std::filesystem::absolute(destPath))
    {
        std::filesystem::create_directories(textureDir, ec);
        std::filesystem::copy_file(sourceAbsPath, destPath,std::filesystem::copy_options::overwrite_existing, ec);
        if (ec)
            std::cerr << "[Scene] Failed to import texture: " << ec.message() << std::endl;
    }
 
    return fileName;
}

SceneObject& Scene::AddObject(PrimitiveTypeObj type, std::string textureDiff,std::string textureSpec)
{
    nameCounters[type]++;

    SceneObject obj;
    obj.name = TypeName(type) + " " + std::to_string(nameCounters[type]);
    obj.type = type;
    obj.shape = GetPrimitiveShape(type);
    
    obj.diffuseTex = getTexture(textureDiff);
    obj.specularTex = getTexture(textureSpec);
    obj.nameDiffTexture = std::filesystem::path(textureDiff).filename().string();
    obj.nameSpecTexture = std::filesystem::path(textureSpec).filename().string();

    obj.shader = defaultShader;

    if (type == PrimitiveTypeObj::Grid)
    {
        objects.push_back(obj);
        RegenerateMesh(objects.back());
        return objects.back();
    }

    objects.push_back(obj);
    return objects.back();
}

void Scene::RegenerateMesh(SceneObject& obj)
{
    Mesh* newMesh = BuildMesh(obj);
    Shape* newShape = new Shape(newMesh, newMesh->drawMode, newMesh->withTexture, newMesh->withNormals);
    newMesh->clearCPUData();

    // se o objeto já tinha uma malha exclusiva de uma edição anterior, e liberado o antigo
    if (obj.ownedMesh != nullptr)
    {
        delete obj.shape;
        delete obj.ownedMesh;
    }

    obj.shape = newShape;
    obj.ownedMesh = newMesh;
}

void Scene::CopyObject(SceneObject& objToBeCopied)
{
    nameCounters[objToBeCopied.type]++;
    
    SceneObject obj = objToBeCopied;
    obj.name = TypeName(objToBeCopied.type) + " " + std::to_string(nameCounters[objToBeCopied.type]);

    if(objToBeCopied.ownedMesh != nullptr){

        obj.ownedMesh = nullptr;
        RegenerateMesh(obj);
    }

    objects.push_back(obj);
}

void Scene::RemoveObject(int index)
{
    if (index < 0 || index >= (int)objects.size())
        return;

    SceneObject &obj = objects[index];
    if (obj.ownedMesh != nullptr)
    {
        delete obj.shape;
        delete obj.ownedMesh;
    }

    objects.erase(objects.begin() + index);
}

std::vector<SceneObject>& Scene::GetObjects()
{
    return objects;
}

json Scene::ToJson() const
{
    json j;
    j["lightingEnabled"] = lightingEnabled;
    j["light"]["position"] = light.position;
    j["light"]["ambient"]  = light.ambient;
    j["light"]["diffuse"]  = light.diffuse;
    j["light"]["specular"] = light.specular;

    j["objects"] = nlohmann::json::array();

    for (auto& obj : objects)
        j["objects"].push_back(obj);

    return j;
}

void Scene::LoadFromJson(const json& j)
{
    for (auto& obj : objects)
        if (obj.ownedMesh != nullptr) { 
            delete obj.shape; delete obj.ownedMesh; 
        }

    objects.clear();
    selectedIndex = -1;

    lightingEnabled = j.value("lightingEnabled", false);
    if (j.contains("light"))
    {
        light.position = j["light"]["position"].get<glm::vec3>();
        light.ambient  = j["light"]["ambient"].get<glm::vec3>();
        light.diffuse  = j["light"]["diffuse"].get<glm::vec3>();
        light.specular = j["light"]["specular"].get<glm::vec3>();
    }

    for (auto& jo : j["objects"])
    {
        PrimitiveTypeObj type = jo.at("type").get<PrimitiveTypeObj>();
        std::string diffKey = jo.value("nameDiffTexture", std::string(DEFAULT_DIFFUSE_TEXTURE));
        std::string specKey = jo.value("nameSpecTexture", std::string(DEFAULT_SPECULAR_TEXTURE));

        SceneObject& obj = AddObject(type, diffKey, specKey);

        obj.name     = jo.value("name", obj.name);
        obj.position = jo.value("position", obj.position);
        obj.rotation = jo.value("rotation", obj.rotation);
        obj.scale    = jo.value("scale", obj.scale);
        obj.color    = jo.value("color", obj.color);
        obj.ambient  = jo.value("ambient", obj.ambient);
        obj.specular = jo.value("specular", obj.specular);
        obj.shininess = jo.value("shininess", obj.shininess);

        obj.slices     = jo.value("slices", obj.slices);
        obj.stacks     = jo.value("stacks", obj.stacks);
        obj.capBottom  = jo.value("capBottom", obj.capBottom);
        obj.capTop     = jo.value("capTop", obj.capTop);
        obj.radius     = jo.value("radius", obj.radius);
        obj.baseRadius = jo.value("baseRadius", obj.baseRadius);
        obj.topRadius  = jo.value("topRadius", obj.topRadius);
        obj.height     = jo.value("height", obj.height);
        obj.linesGrid   = jo.value("linesGrid", obj.linesGrid);
        obj.columnsGrid = jo.value("columnsGrid", obj.columnsGrid);
        obj.tilePerCellMode = jo.value("tileMode", 0) != 0;
        obj.cellSize    = jo.value("cellSize", obj.cellSize);

        if (jo.contains("slices") || jo.contains("radius") || jo.contains("baseRadius") || jo.contains("linesGrid")|| jo.contains("columnsGrid") || jo.contains("cellSize")|| jo.contains("tileMode"))
            RegenerateMesh(obj);
    }
}

bool Scene::saveScene(const std::string& pathScene){

    std::ofstream file(pathScene);
    if (!file.is_open())
    {
        std::cerr << "[Scene] Error save scene: " << pathScene << std::endl;
        return false;
    }
 
    file << ToJson().dump(4);
    return true;
}

bool Scene::loadScene(const std::string& pathScene){

    std::ifstream file(pathScene);
    if (!file.is_open())
    {
        std::cerr << "[Scene] Error loading scene: " << pathScene << std::endl;
        return false;
    }
 
    nlohmann::json j;
    file >> j;
    LoadFromJson(j);

    return true;

}
