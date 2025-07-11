#ifndef CUBE_HPP
#define CUBE_HPP

#include "Shape.hpp"

class Cube : public Shape{

public:
    Cube(
        const std::string texturePath = "",
        bool lightingEnabled = false,
        const char *vertexPath = DEFAULT_CUBE_VERTEX,
        const char *fragmentPath = DEFAULT_CUBE_FRAGMENT
    );
    
    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};



#endif
