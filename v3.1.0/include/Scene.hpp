#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "SceneObject.hpp"
#include "Mesh.hpp"
#include "Shape.hpp"
#include "Shader.hpp"


struct SceneLight
{
    glm::vec3 position = glm::vec3(3.0f, 3.0f, 3.0f);
    glm::vec3 ambient  = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse  = glm::vec3(0.6f, 0.6f, 0.6f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Scene
{
public:
    explicit Scene(Shader* defaultShader);
    ~Scene();

    SceneObject& AddObject(PrimitiveTypeObj type);
    void RemoveObject(int index);
    void RegenerateMesh(SceneObject& obj);

    std::vector<SceneObject>& GetObjects();

    // Retorna a malha compartilhada (cache) 
    Shape* GetPrimitiveShape(PrimitiveTypeObj type);


    bool lightingEnabled = false;
    int selectedIndex = -1;
    SceneLight light;

private:
    std::vector<SceneObject> objects;

    std::unordered_map<PrimitiveTypeObj, Mesh*>  meshCache;
    std::unordered_map<PrimitiveTypeObj, Shape*> shapeCache;
    std::unordered_map<PrimitiveTypeObj, int>    nameCounters;

    Shader* defaultShader;

    Mesh* BuildMesh(const SceneObject& obj);
    std::string TypeName(PrimitiveTypeObj type);
};