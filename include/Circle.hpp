#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include <vector>
#include "../dep/glm/glm.hpp"

class Circle : public Shape {
private:
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Shader shader;
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    void generateCircle(float radius, int segments);

public:
    Circle();
    Circle(const char* vertexPath, const char* fragmentPath);
    ~Circle();

    void desenhar() override;
    Shader& getShader();
};

#endif
