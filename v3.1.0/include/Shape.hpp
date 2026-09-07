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
public:
    VAO vao;
    Mesh* mesh = nullptr;
    GLenum drawMode;
    GLsizei indexCount = 0;
    GLsizei verticesCount = 0;
    bool lightingEnabled;
    bool textureEnabled;

public:
    void setupVAO();
    void drawObject();

    Shape(Mesh *mesh, GLenum drawMode , bool textureEnabled = false, bool lightingEnabled = false);
};

#endif