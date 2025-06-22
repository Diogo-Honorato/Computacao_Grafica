#ifndef LINE_HPP
#define LINE_HPP

#include "Shape.hpp"
#include <vector>

class Line : public Shape {
private:
    std::vector<float>& points;
    std::vector<GLuint>& indices;
    float lineWidth;

public:
    Line(
        std::vector<float>& pointsRef,
        std::vector<GLuint>& indicesRef,
        float lineWidth = 1.0f,
        const char* vertexPath = DEFAULT_LINE_VERTEX,
        const char* fragmentPath = DEFAULT_LINE_FRAGMENT
    );

    static std::vector<float> generateParabolaPoints(float a, float b, float c, float xStart, float xEnd, int segments
    );

    static std::vector<GLuint> generateLineIndices(int pointCount);

    void generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) override;
    void setup() override;
    void desenhar() override;
};

#endif