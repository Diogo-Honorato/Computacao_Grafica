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
    std::optional<glm::mat4> modelMatrix;

public:
    Triangle();
    Triangle(const Shader& customShader);
    ~Triangle();

    void setModelMatrix(const glm::mat4& model);
    void desenhar() override;
};

#endif