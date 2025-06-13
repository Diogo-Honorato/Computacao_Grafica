#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Paths.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

class Shape {
protected:
    VAO vao;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;
    Shader shader;

public:
    virtual void desenhar() = 0;
    virtual void setup() = 0;
    
    Shader& getShader();

    Shape(const char* vertexPath, const char* fragmentPath);
    virtual ~Shape();
};

#endif