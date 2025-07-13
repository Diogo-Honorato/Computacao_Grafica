#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <iostream>
#include <random>
#include <memory>
#include <vector>
#include "Shape.hpp"

// Códigos de região
const int INSIDE = 0; // 0000
const int LEFT_SIDE = 1;   // 0001
const int RIGHT_SIDE = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

class Clipping {
private:
    float x_min, y_min, x_max, y_max;
    std::vector<std::unique_ptr<Shape>> clippedLines;
    std::vector<std::unique_ptr<Shape>> originalLines;
    glm::vec3 insideColor = glm::vec3(0.0f, 0.0f, 1.0f); // Azul para dentro
    glm::vec3 outsideColor = glm::vec3(1.0f, 0.0f, 0.0f); // Vermelho para fora
    Shape *tela;
    Shader *sh;
    Shader *tsh;

public:
    Clipping(float xmin = -0.5f,float ymin = -0.5f,float xmax = 0.5f,float ymax = 0.5f);
    ~Clipping();
    void generateRandomLines();
    void draw();

private:
    int computeCode(float x, float y);
    void clipLine(float x1, float y1, float x2, float y2);
};

#endif