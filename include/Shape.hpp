#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Shader.hpp"

class Shape {
public:
    virtual void desenhar() = 0;
    virtual Shader& getShader() = 0;
    virtual ~Shape() = default;
};

#endif