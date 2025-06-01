#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "../dep/glm/glm.hpp"
#include <optional>

class Triangle : public Shape {
private:
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Shader shader;

public:
    Triangle();
    Triangle(const Shader& customShader);
    ~Triangle();

    void desenhar() override;
    Shader getShader();
};

#endif