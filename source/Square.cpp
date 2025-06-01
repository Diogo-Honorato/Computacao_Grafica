#include "../include/Square.hpp"

float squareVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint squareIndices[] = {
    0, 1, 2,
    2, 3, 0
};

Square::Square() : shader("../shader/basic_shaders/vertex/basic_square.vs", "../shader/basic_shaders/fragment/basic_square.fs") {
    vao.Bind();
    vbo = new VBO(squareVertices, sizeof(squareVertices));
    ebo = new EBO(squareIndices, sizeof(squareIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

Square::Square(const Shader& customShader) : shader(customShader) {
    vao.Bind();
    vbo = new VBO(squareVertices, sizeof(squareVertices));
    ebo = new EBO(squareIndices, sizeof(squareIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

Square::~Square() {
    delete vbo;
    delete ebo;
}

void Square::desenhar() {

    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

Shader& Square::getShader(){
    return shader;
}