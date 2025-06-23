#include "../include/Shape.hpp"

Shape::Shape(const std::string texturePath,const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath), texture(texturePath, GL_TEXTURE_2D, GL_RGBA, true) {}

Shader& Shape::getShader() {
    return shader;
}

void Shape::setTexture(Texture tex) {
    texture = tex;
}

Texture& Shape::getTexture() {
    return texture;
}

Shape::~Shape() {
    if (vbo) delete vbo;
    if (ebo) delete ebo;
}
