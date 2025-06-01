#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "../dep/glm/glm.hpp"

class Square : public Shape {
private:
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Shader shader;

public:
    Square();
    Square(const char* vertexPath, const char* fragmentPath);
    ~Square();

    void desenhar() override;
    Shader& getShader();
};

#endif
