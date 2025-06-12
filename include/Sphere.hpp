// Geração de esfera baseada no método de stacks/slices de Song Ho Ahn
// Fonte original: https://www.songho.ca/opengl/gl_sphere.html
// Código foi adaptado para meu projeto com modificações na estrutura de dados e lógica


#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>
#include <cmath>
#include "Shape.hpp"

class Sphere : public Shape{

private:
    std::vector<float> verticeAttribs;
    std::vector<unsigned int> indices;

    void generateSphere(float radius, int slices, int stacks);

public:
    Sphere();
    Sphere(float radius, int slices, int stacks,const char* vertexPath, const char* fragmentPath);
    void desenhar() override;
    void setup() override;
};
#endif