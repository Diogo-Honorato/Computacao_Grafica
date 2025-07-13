#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include "Paths.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "../dep/glm/glm.hpp"

class Shape {
protected:
    VAO vao;
    Mesh* mesh = nullptr;
    Texture* texture = nullptr;
    Shader* shader = nullptr;
    GLsizei indexCount = 0;
    GLsizei verticesCount = 0;
    bool lightingEnabled;

public:
    void setupVAO();
    void desenharElem();
    void desenharArrays();
    void desenharLine();
    
    Shader* getShader();
    Texture* getTexture();

    Shape(Mesh *mesh, Shader* shader, Texture *tex = nullptr, bool lightingEnabled = false);
};

#endif