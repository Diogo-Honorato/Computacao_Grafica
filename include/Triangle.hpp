#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
public:

    Triangle(        
        const char *vertexPath = DEFAULT_TRIANGLE_VERTEX,
        const char *fragmentPath = DEFAULT_TRIANGLE_FRAGMENT
    );

    void setup() override;
    void desenhar() override;
};

#endif