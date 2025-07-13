#include "../include/Shape.hpp"

Shape::Shape(const std::string &texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath), lightingEnabled(lightingEnabled) 
{

    if(!texturePath.empty()){

        texture = new Texture(texturePath, GL_TEXTURE_2D, GL_RGBA, true);
    }
}

Shader& Shape::getShader() {
    return shader;
}

void Shape::setTexture(Texture *tex) {
    if (texture) delete texture;
    texture = tex;
}

Texture* Shape::getTexture() {
    return texture;
}

Shape::~Shape() {
    if  (vbo) delete vbo;
    if  (ebo) delete ebo;
    if  (texture) delete texture;
}
