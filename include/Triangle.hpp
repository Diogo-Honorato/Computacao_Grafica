#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
public:
    Triangle();
    Triangle(const char* vertexPath, const char* fragmentPath);
    void setup() override;
    void desenhar() override;
};

#endif