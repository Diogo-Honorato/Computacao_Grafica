// Geração de esfera baseada no método de stacks/slices de Song Ho Ahn
// Fonte original: https://www.songho.ca/opengl/gl_sphere.html
// Código foi adaptado para meu projeto com modificações na estrutura de dados e lógica


#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include <cmath>
#include "Shape.hpp"

/*
Calculo:
    total de indices:   slices * (stacks - 1) * 6
    total de vertices:  (slices + 1) * (stacks + 1)
    total de triangulos:(total de indices / 3)
*/
class Sphere : public Shape{

private:
    float radius; 
    int slices; 
    int stacks;

public:
    Sphere(
        float radius = 1.0f, int slices = 36, int stacks = 18,
        const std::string texturePath = "",
        bool lightingEnabled = false,
        const char *vertexPath = DEFAULT_SPHERE_VERTEX,
        const char *fragmentPath = DEFAULT_SPHERE_FRAGMENT
    );
    
    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};
#endif
