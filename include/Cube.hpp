#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shape.hpp"

class Cube : public Shape{

public:
    Cube(        
        const char *vertexPath = DEFAULT_CUBE_VERTEX,
        const char *fragmentPath = DEFAULT_CUBE_FRAGMENT
    );
    void setup() override;
    void desenhar() override;
};



#endif