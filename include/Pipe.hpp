#ifndef PIPE_HPP
#define PIPE_HPP

#include <cmath>
#include "Shape.hpp"
#include <vector>


class Pipe : public Shape {
private:

    std::vector<glm::vec3>& pathPoints;

    float topRadius;
    float baseRadius;
    int slices;

    void calculateFrenetFrame(const glm::vec3& tangent, glm::vec3& normal, glm::vec3& binormal);
    void calculatePathTangents(const std::vector<glm::vec3>& path, std::vector<glm::vec3>& tangents);
    std::vector<float>buildUnitCircleVertices();

public:
    Pipe(std::vector<glm::vec3>& pathPoints,float topRadius=0.5f,float baseRadius=0.5f,int slices = 16, const std::string texturePath = nullptr,const char* vertexPath=DEFAULT_PIPE_VERTEX, const char* fragmentPath=DEFAULT_PIPE_FRAGMENT);
    
    static std::vector<glm::vec3> generateTorus(int segments, float radius);
    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif