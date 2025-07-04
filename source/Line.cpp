#include "../include/Line.hpp"
#include <cmath>

Line::Line(std::vector<float>& pointsRef, std::vector<GLuint>& indicesRef,const char* vertexPath, const char* fragmentPath)
    : Shape("",false,vertexPath, fragmentPath),points(pointsRef),indices(indicesRef) {
    
    setup();
}

std::vector<float> Line::generateParabolaPoints(float a, float b, float c, float xStart, float xEnd, int segments) {
    
    std::vector<float> parabolaPoints;
    parabolaPoints.reserve((segments + 1) * 3);

    float step = (xEnd - xStart) / segments;
    for (int i = 0; i <= segments; ++i) {
        float x = xStart + i * step;
        float y = a * x * x + b * x + c;
        parabolaPoints.push_back(x);
        parabolaPoints.push_back(y);
        parabolaPoints.push_back(0.0f); // z = 0
    }
    return parabolaPoints;
}

std::vector<GLuint> Line::generateLineIndices(int pointCount) {
    std::vector<GLuint> lineIndices;
    if (pointCount < 2) return lineIndices;

    lineIndices.reserve((pointCount - 1) * 2);
    for (int i = 0; i < pointCount - 1; ++i) {
        lineIndices.push_back(i);
        lineIndices.push_back(i + 1);
    }
    return lineIndices;
}

void Line::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {
    vertices = points;
    indices = this->indices;
}

void Line::setup() {

    indexCount = indices.size();
    vao.Bind();
    
    vbo = new VBO(points.data(), points.size() * sizeof(float));
    
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

void Line::desenhar() {
    
    vao.Bind();
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
