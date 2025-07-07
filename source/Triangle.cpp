#include "../include/Triangle.hpp"

Triangle::Triangle(const std::string texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath) : Shape(texturePath,lightingEnabled,vertexPath, fragmentPath) {
    setup();
}

void Triangle::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {
    // Posições dos vértices
    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f}
    };

    // Coordenadas de textura
    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {0.5f, 1.0f}
    };

    glm::vec3 normal(0.0f, 0.0f, 1.0f);

    vertices.clear();
    for (int i = 0; i < 3; ++i) {
        // posição
        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);

        // textura
        if (texture != nullptr) {
            vertices.push_back(texCoords[i].x);
            vertices.push_back(texCoords[i].y);
        }

        // normal
        if (lightingEnabled) {
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    indices = { 0, 1, 2 };
}


void Triangle::setup() {
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    generateMesh(vertices, indices);
    indexCount = static_cast<GLsizei>(indices.size());

    vao.Bind();

    unsigned int stride = 3;
    if (texture != nullptr) stride += 2;
    if (lightingEnabled) stride += 3;

    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // textura
    if (texture != nullptr) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    // normal
    if (lightingEnabled) {
        int offset = (texture != nullptr) ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}


void Triangle::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
