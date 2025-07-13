#include "../include/Square.hpp"

Square::Square(const std::string texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath)
    : Shape(texturePath,lightingEnabled,vertexPath, fragmentPath) {
    setup();
}

void Square::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.5f,  0.5f, 0.0f},
        {-0.5f,  0.5f, 0.0f}
    };

    // Coordenadas de textura (s, t)
    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };

    // Normal para todos os vértices
    glm::vec3 normal(1.0f, 1.0f, 0.0f);

    vertices.clear();
    for (int i = 0; i < 4; ++i) {
        // Posição
        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);

        // Textura
        if (texture != nullptr) {
            vertices.push_back(texCoords[i].x);
            vertices.push_back(texCoords[i].y);
        }

        // Normal
        if (lightingEnabled) {
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    indices = {
        0, 1, 2,
        2, 3, 0
    };
}


void Square::setup() {
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

    // posição
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


void Square::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
