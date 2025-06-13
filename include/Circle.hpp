#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"
#include <vector>

class Circle : public Shape {

private:
    float radius;
    int segments;

public:
    Circle(
        float radius = 0.5f, int segments = 50,
        const char *vertexPath = DEFAULT_CIRCLE_VERTEX,
        const char *fragmentPath = DEFAULT_CIRCLE_FRAGMENT
    );

    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif
