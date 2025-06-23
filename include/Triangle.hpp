#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
public:

    Triangle(
        const std::string texturePath = nullptr,        
        const char *vertexPath = DEFAULT_TRIANGLE_VERTEX,
        const char *fragmentPath = DEFAULT_TRIANGLE_FRAGMENT
    );

    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif