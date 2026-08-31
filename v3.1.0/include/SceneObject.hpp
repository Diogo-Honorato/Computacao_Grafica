#pragma once

#include "../dep/glm/glm.hpp"
#include "../dep/glm/gtc/matrix_transform.hpp"
#include <string>
#include "Shape.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

enum class PrimitiveTypeObj
{
    Cube,
    Sphere,
    Circle,
    Triangle,
    Square,
    Cylinder,
    Paraboloid,
};

struct SceneObject
{

    std::string name = "Object";
    PrimitiveTypeObj type = PrimitiveTypeObj::Cube;


    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale    = glm::vec3(1.0f);


    glm::vec3 color    = glm::vec3(1.0f);
    glm::vec3 ambient  = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(0.5f);
    float shininess = 32.0f;


    bool useTexture  = false;
    Texture* diffuseTex  = nullptr;
    Texture* specularTex = nullptr;

    //Parâmetros de geração de malha
    int   slices     = 36;
    int   stacks     = 18;
    bool  capBottom  = true;
    bool  capTop     = true;
    float radius     = 1.0f;
    float baseRadius = 1.0f;
    float topRadius  = 1.0f;
    float height     = 2.0f;

    Shape*  shape  = nullptr;
    Shader* shader = nullptr;


    bool  ownsShape  = false;
    Mesh* ownedMesh  = nullptr;

    glm::mat4 GetModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }
};