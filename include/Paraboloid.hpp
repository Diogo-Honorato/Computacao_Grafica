#ifndef PARABOLOID_HPP
#define PARABOLOID_HPP

#include <vector>
#include <cmath>
#include "Shape.hpp"

class Paraboloid : public Shape {
private:
    float height;
    float radius;
    int slices;
    int stacks;
    bool hasBottomCap;
    bool hasTopCap;

public:
    Paraboloid(bool hasBottomCap = false,bool hasTopCap = false,float height = 1.0f, float radius = 1.0f, int slices = 36, int stacks = 18,
        const std::string texturePath = "",
        const char* vertexPath = DEFAULT_PARAB_VERTEX,
        const char* fragmentPath = DEFAULT_PARAB_FRAGMENT
    );
    
    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif
