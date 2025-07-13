// Geração de  Cilindro e Prisma OpenGL no método de stacks/slices de Song Ho Ahn
// Fonte original: https://www.songho.ca/opengl/gl_cylinder.html
// Código foi adaptado para meu projeto com modificações na estrutura de dados e lógica

#ifndef AXIALEXTRUDER_H
#define AXIALEXTRUDER_H

#include "Shape.hpp"
#include <vector>

class AxialExtruder : public Shape
{
private:
    float baseRadius;
    float topRadius;
    float height;
    int slices;
    int stacks;

public:
    AxialExtruder(float topRadius = 1.0f, float baseRadius = 1.0f, float height = 2.0f, int slices = 36, int stacks = 8,
                  const std::string texturePath ="",
                  bool lightingEnabled = false,
                  const char *vertexPath = DEFAULT_EXTRUDER_VERTEX,
                  const char *fragmentPath = DEFAULT_EXTRUDER_FRAGMENT
    );

    std::vector<float>buildUnitCircleVertices();
    void generateMesh(std::vector<float> &vertices, std::vector<GLuint> &indices) override;
    void setup() override;
    void desenhar() override;
};
#endif
