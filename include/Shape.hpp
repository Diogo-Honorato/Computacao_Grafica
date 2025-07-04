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
    Texture* texture = nullptr;
    Shader shader;
    GLsizei indexCount = 0;
    bool lightingEnabled;

public:
    virtual void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) = 0;
    virtual void setup() = 0;
    virtual void desenhar() = 0;
    
    Shader& getShader();
    Texture* getTexture();
    void setTexture(Texture *tex);

    Shape(const std::string &texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath);
    virtual ~Shape();
};

#endif