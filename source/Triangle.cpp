#include "../include/Triangle.hpp"

float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint triangleIndices[] = {
    0, 1, 2
};

Triangle::Triangle() : Shape("../shader/basic_shaders/vertex/basic_triangle.vs", "../shader/basic_shaders/fragment/basic_triangle.fs") {
    setup();
}

Triangle::Triangle(const char* vertexPath, const char* fragmentPath) : Shape(vertexPath, fragmentPath) {
    setup();
}

void Triangle::setup() {
    vao.Bind();
    vbo = new VBO(triangleVertices, sizeof(triangleVertices));
    ebo = new EBO(triangleIndices, sizeof(triangleIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    vao.Unbind();
}

void Triangle::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
