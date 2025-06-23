#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include "Paths.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include "../dep/glm/glm.hpp"

class Shape {
protected:
    VAO vao;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;
    Texture texture;
    Shader shader;
    GLsizei indexCount = 0;

public:
    virtual void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) = 0;
    virtual void setup() = 0;
    virtual void desenhar() = 0;
    
    Shader& getShader();
    Texture& getTexture();
    void setTexture(Texture tex);

    Shape(const std::string texturePath,const char* vertexPath, const char* fragmentPath);
    virtual ~Shape();
};

#endif