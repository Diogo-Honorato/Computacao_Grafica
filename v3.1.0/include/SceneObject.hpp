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
    Grid,
};

struct SceneObject
{

    std::string name = "Object";
    PrimitiveTypeObj type = PrimitiveTypeObj::Cube;

    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 scale    = glm::vec3(1.0f);


    glm::vec3 color    = glm::vec3(1.0f);
    glm::vec3 ambient  = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(0.5f);
    float shininess = 32.0f;

    std::string nameDiffTexture;
    std::string nameSpecTexture;
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

    //Parâmetros de geração do grid
    int linesGrid   = 10;
    int columnsGrid = 10;

    Shape*  shape  = nullptr;
    Shader* shader = nullptr;


    bool  ownsShape  = false;
    Mesh* ownedMesh  = nullptr;

    glm::mat4 GetModelMatrix() const
    {
         
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        model *= glm::mat4_cast(rotation); 
        model = glm::scale(model, scale);
        return model;
    }
};