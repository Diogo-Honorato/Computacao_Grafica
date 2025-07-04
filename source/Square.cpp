#include "../include/Square.hpp"

Square::Square(const std::string texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath)
    : Shape(texturePath,lightingEnabled,vertexPath, fragmentPath) {
    setup();
}

void Square::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {
    
    vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    indices = {
        0, 1, 2,
        2, 3, 0
    };
}

void Square::setup() {

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

void Square::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
