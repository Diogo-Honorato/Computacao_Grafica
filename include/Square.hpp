#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"

class Square : public Shape {
public:
    Square();
    Square(const char* vertexPath, const char* fragmentPath);
    void setup() override;
    void desenhar() override;
};

#endif
