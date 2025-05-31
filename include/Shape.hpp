#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape {
public:
    virtual void desenhar() = 0;
    virtual ~Shape() = default;
};

#endif