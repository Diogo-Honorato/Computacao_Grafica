#include "../include/Triangle.hpp"

Triangle::Triangle(const std::string texturePath,const char* vertexPath, const char* fragmentPath) : Shape(texturePath,vertexPath, fragmentPath) {
    setup();
}

void Triangle::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices){

    vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    indices = {
        0, 1, 2
    };
}

void Triangle::setup() {

    std::vector<float>vertices;
    std::vector<GLuint>indices;

    generateMesh(vertices,indices);

    indexCount = static_cast<GLsizei>(indices.size());

    vao.Bind();

    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    vao.Unbind();
}

void Triangle::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
