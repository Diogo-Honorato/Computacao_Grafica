#include "../include/Paraboloid.hpp"

Paraboloid::Paraboloid(bool hasBottomCap,bool hasTopCap,float height, float radius, int slices, int stacks,const std::string texturePath ,const char* vertexPath, const char* fragmentPath)
    : Shape(texturePath,vertexPath, fragmentPath),hasBottomCap(hasBottomCap),hasTopCap(hasTopCap),height(height),radius(radius),slices(slices),stacks(stacks)
{

    setup();
}

void Paraboloid::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices) {

    vertices.clear();
    indices.clear();
    
    // Gerar vértices
    for (int i = 0; i <= stacks; ++i) {
        float stackRatio = static_cast<float>(i) / stacks;
        float y = height * stackRatio;
        float currentRadius = radius * sqrtf(stackRatio);
        
        for (int j = 0; j <= slices; ++j) {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;
            
            float x = currentRadius * cosf(sliceAngle);
            float z = currentRadius * sinf(sliceAngle);
            
            // Posição
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            
            // Coordenadas de textura
            vertices.push_back(static_cast<float>(j) / slices);
            vertices.push_back(stackRatio);
        }
    }
    
    // Gerar índices para as faces laterais
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int first = (i * (slices + 1)) + j;
            int second = first + (slices + 1);
            
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    
    // Gerar tampa inferior se necessário
    if (hasBottomCap) {
        int centerIndex = vertices.size() / 5; // 5 floats por vértice (pos(3) + tex(2))
        
        // Vértice central da tampa
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        // Coordenadas de textura
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);
        
        // Vértices da borda da tampa
        for (int j = 0; j <= slices; ++j) {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;
            float x = radius * cosf(sliceAngle);
            float z = radius * sinf(sliceAngle);
            
            // Posição (y = 0)
            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(z);
            
            
            // Coordenadas de textura
            vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
            vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
        }
        
        // Índices para a tampa
        for (int j = 0; j < slices; ++j) {
            indices.push_back(centerIndex);
            indices.push_back(centerIndex + j + 1);
            indices.push_back(centerIndex + j + 2);
        }
    }

    // Gerar tampa superior se necessário
    if (hasTopCap) {
        int topBaseIndex = vertices.size() / 5; // Índice base para novos vértices
        
        // Vértice central da tampa superior
        vertices.push_back(0.0f);
        vertices.push_back(height);
        vertices.push_back(0.0f);
        
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);
        
        // Vértices da borda da tampa superior
        for (int j = 0; j <= slices; ++j) {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;
            float x = radius * cosf(sliceAngle);
            float z = radius * sinf(sliceAngle);
            
            vertices.push_back(x);
            vertices.push_back(height);
            vertices.push_back(z);

            vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
            vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
        }
        
        // Índices para a tampa superior (sentido inverso para face visível)
        for (int j = 0; j < slices; ++j) {
            indices.push_back(topBaseIndex);
            indices.push_back(topBaseIndex + j + 2);
            indices.push_back(topBaseIndex + j + 1);
        }
    }
}

void Paraboloid::setup() {
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    
    generateMesh(vertices, indices);
    indexCount = indices.size();
    
    vao.Bind();
    
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.Unbind();
}

void Paraboloid::desenhar() {

    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}