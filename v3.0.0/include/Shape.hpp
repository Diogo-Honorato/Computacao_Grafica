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
    GLsizei indexCount = 0;
    GLsizei verticesCount = 0;
    bool lightingEnabled;
    bool textureEnabled;

public:
    void setupVAO();
    void desenharElem();
    void desenharArrays();
    void desenharLine();
    
    Shape(Mesh *mesh, bool textureEnabled = false,bool lightingEnabled = false);
};

#endif