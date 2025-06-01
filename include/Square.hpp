#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "../dep/glm/glm.hpp"
#include <optional>

class Square : public Shape {
private:
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Shader shader;
    std::optional<glm::mat4> modelMatrix;

public:
    Square();
    Square(const Shader& customShader);
    ~Square();

    void setModelMatrix(const glm::mat4& model);
    void desenhar() override;
};

#endif
