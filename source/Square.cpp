#include "../include/Square.hpp"

static float squareVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

static GLuint squareIndices[] = {
    0, 1, 2,
    2, 3, 0
};

Square::Square(const char* vertexPath, const char* fragmentPath)
    : Shape(vertexPath, fragmentPath) {
    setup();
}

void Square::setup() {
    vao.Bind();
    vbo = new VBO(squareVertices, sizeof(squareVertices));
    ebo = new EBO(squareIndices, sizeof(squareIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

void Square::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
