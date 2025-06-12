#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shape.hpp"

class Cube : public Shape{

public:
    Cube();
    Cube(const char* vertexPath, const char* fragmentPath);
    void setup() override;
    void desenhar() override;
};



#endif