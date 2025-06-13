#include "../include/Shape.hpp"

Shape::Shape(const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath) {}

Shader& Shape::getShader() {
    return shader;
}

void Shape::setTexture(Texture* tex) {
    texture = tex;
}

Texture* Shape::getTexture() {
    return texture;
}

Shape::~Shape() {
    if (vbo) delete vbo;
    if (ebo) delete ebo;
    if (texture) delete texture;
}
