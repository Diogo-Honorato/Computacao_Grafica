#include "../include/Triangle.hpp"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint indices[] = {
    0, 1, 2
};

Triangle::Triangle(): shader("../shader/basic_shaders/vertex/basic_triangle.vs", "../shader/basic_shaders/fragment/basic_triangle.fs"){
    vao.Bind();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

Triangle::Triangle(const Shader& customShader): shader(customShader){
    vao.Bind();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

Triangle::~Triangle() {
    delete vbo;
    delete ebo;
}

void Triangle::setModelMatrix(const glm::mat4& model) {
    modelMatrix = model;
}

void Triangle::desenhar() {
    
    shader.useShaders();

    if (modelMatrix.has_value()) {
        shader.setMat4("model", modelMatrix.value());
    }

    vao.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
