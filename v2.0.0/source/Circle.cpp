#include "../include/Circle.hpp"
#include <cmath>


Circle::Circle(float radius, int segments, const std::string texturePath,bool lightingEnabled,const char* vertexPath, const char* fragmentPath)
    : Shape(texturePath,lightingEnabled,vertexPath, fragmentPath), radius(radius), segments(segments){
    
    setup();
}


void Circle::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {
    // Centro do círculo
    vertices.push_back(0.0f); // x
    vertices.push_back(0.0f); // y
    vertices.push_back(0.0f); // z

    if (texture != nullptr) {
        vertices.push_back(0.5f); // s
        vertices.push_back(0.5f); // t
    }

    if (lightingEnabled) {
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
    }

    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * M_PI / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Posição
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        // textura
        if (texture != nullptr) {
            float s = 0.5f + 0.5f * cos(angle);
            float t = 0.5f + 0.5f * sin(angle);
            vertices.push_back(s);
            vertices.push_back(t);
        }

        // Normal
        if (lightingEnabled) {
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
        }

        // indices
        if (i > 0) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
}


void Circle::setup() {
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

    if (texture != nullptr) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled) {
        int offset = (texture != nullptr) ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}


void Circle::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}