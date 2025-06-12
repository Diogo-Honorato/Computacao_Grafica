#include "../include/Shape.hpp"

Shape::Shape(const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath) {}

Shader& Shape::getShader() {
    return shader;
}

Shape::~Shape() {
    if (vbo) delete vbo;
    if (ebo) delete ebo;
}
