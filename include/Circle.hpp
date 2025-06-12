#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"
#include <vector>

class Circle : public Shape {

private:
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    void generateCircle(float radius, int segments);

public:
    Circle();
    Circle(const char* vertexPath, const char* fragmentPath);

    void desenhar() override;
    void setup() override;
};

#endif
