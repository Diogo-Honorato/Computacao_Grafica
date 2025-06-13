#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"

class Square : public Shape {
public:

    Square(        
        const char *vertexPath = DEFAULT_SQUARE_VERTEX,
        const char *fragmentPath = DEFAULT_SQUARE_FRAGMENT
    );

    void setup() override;
    void desenhar() override;
};

#endif
