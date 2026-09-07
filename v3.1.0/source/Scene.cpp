#include "../include/Scene.hpp"

Scene::Scene(Shader* defaultShader) : defaultShader(defaultShader) {

    textureCache[DEFAULT_DIFFUSE_TEXTURE] = new Texture(255, 255, 255, 255);
    textureCache[DEFAULT_SPECULAR_TEXTURE] = new Texture(0, 0, 0, 255);
}

Scene::~Scene()
{
    for (auto &obj : objects)
    {
        if (obj.ownsShape)
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

Texture* Scene::getTexture(std::string nameTexture){

    auto it = textureCache.find(nameTexture);
    if(it != textureCache.end())
        return it->second;

    
    Texture* tex = new Texture(nameTexture);
    textureCache[nameTexture] = tex;
    
    return tex;
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
    obj.nameDiffTexture = textureDiff;
    obj.nameSpecTexture = textureSpec;

    obj.shader = defaultShader;
    obj.ownsShape = false; // começa usando a malha compartilhada do cache

    objects.push_back(obj);
    return objects.back();
}

void Scene::RegenerateMesh(SceneObject& obj)
{
    Mesh* newMesh = BuildMesh(obj);
    Shape* newShape = new Shape(newMesh, newMesh->drawMode, newMesh->withTexture, newMesh->withNormals);
    newMesh->clearCPUData();

    // se o objeto já tinha uma malha exclusiva de uma edição anterior, e liberado o antigo
    if (obj.ownsShape)
    {
        delete obj.shape;
        delete obj.ownedMesh;
    }

    obj.shape = newShape;
    obj.ownedMesh = newMesh;
    obj.ownsShape = true;
}

void Scene::RemoveObject(int index)
{
    if (index < 0 || index >= (int)objects.size())
        return;

    SceneObject &obj = objects[index];
    if (obj.ownsShape)
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