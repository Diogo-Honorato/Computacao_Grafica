#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Shape.hpp"

class Square : public Shape {
public:

    Square(
        const std::string texturePath = "",
        bool lightingEnabled = false,    
        const char *vertexPath = DEFAULT_SQUARE_VERTEX,
        const char *fragmentPath = DEFAULT_SQUARE_FRAGMENT
    );

    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif
