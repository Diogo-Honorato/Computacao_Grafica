#include "../include/Circle.hpp"
#include <cmath>

Circle::Circle() : shader("../shader/basic_shaders/vertex/basic_circle.vs", "../shader/basic_shaders/fragment/basic_circle.fs") {
    generateCircle(0.5f, 50);
    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    vao.Unbind();
}

Circle::Circle(const char* vertexPath, const char* fragmentPath): shader(vertexPath,fragmentPath) {
    generateCircle(0.5f, 50);
    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    vao.Unbind();
}

Circle::~Circle() {
    delete vbo;
    delete ebo;
}

void Circle::generateCircle(float radius, int segments) {
    vertices.push_back(0.0f); // x
    vertices.push_back(0.0f); // y
    vertices.push_back(0.0f); // z

    for (int i = 0; i <= segments; ++i) {

        float angle = i * 2.0f * M_PI / segments;
        vertices.push_back(radius * cos(angle));
        vertices.push_back(radius * sin(angle));
        vertices.push_back(0.0f);
        if (i > 0) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
}

void Circle::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

Shader& Circle::getShader(){
    return shader;
}