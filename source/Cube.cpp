#include "../include/Cube.hpp"

Cube::Cube(const char* vertexPath, const char* fragmentPath) 
    : Shape(vertexPath, fragmentPath){

    setup();
}

void Cube::generateMesh(std::vector<float>& vertexData, std::vector<GLuint>& indexData) {
    
    const float positions[8][3] = {
        {-0.5f, -0.5f, -0.5f}, // 0
        { 0.5f, -0.5f, -0.5f}, // 1
        { 0.5f,  0.5f, -0.5f}, // 2
        {-0.5f,  0.5f, -0.5f}, // 3
        {-0.5f, -0.5f,  0.5f}, // 4
        { 0.5f, -0.5f,  0.5f}, // 5
        { 0.5f,  0.5f,  0.5f}, // 6
        {-0.5f,  0.5f,  0.5f}  // 7
    };

    const float texCoords[4][2] = {
        {0.0f, 0.0f}, // bottom-left
        {1.0f, 0.0f}, // bottom-right
        {1.0f, 1.0f}, // top-right
        {0.0f, 1.0f}  // top-left
    };

    const int faces[6][4] = {
        {0, 1, 2, 3}, // Back
        {5, 4, 7, 6}, // Front
        {1, 5, 6, 2}, // Right
        {4, 0, 3, 7}, // Left
        {3, 2, 6, 7}, // Top
        {4, 5, 1, 0}  // Bottom
    };

    for (int i = 0; i < 6; ++i) {
        int startIndex = vertexData.size() / 5; // cada vértice tem 5 floats

        for (int j = 0; j < 4; ++j) {
            int posIdx = faces[i][j];

            vertexData.push_back(positions[posIdx][0]); // x
            vertexData.push_back(positions[posIdx][1]); // y
            vertexData.push_back(positions[posIdx][2]); // z

            vertexData.push_back(texCoords[j][0]); // u
            vertexData.push_back(texCoords[j][1]); // v
        }

        indexData.push_back(startIndex);
        indexData.push_back(startIndex + 1);
        indexData.push_back(startIndex + 2);

        indexData.push_back(startIndex + 2);
        indexData.push_back(startIndex + 3);
        indexData.push_back(startIndex);
    }
}

void Cube::setup(){
    
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    
    generateMesh(vertices,indices);

    indexCount = static_cast<GLsizei>(indices.size());

    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(vertices[0]));
    ebo = new EBO(indices.data(), indices.size() * sizeof(indices[0]));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    texture = new Texture("../texture/mc50.png", GL_TEXTURE_2D, GL_RGBA, true);

    vao.Unbind();
}


void Cube::desenhar() {

    texture->Bind(GL_TEXTURE0);
    vao.Bind();
    glDrawElements(GL_TRIANGLES,indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
    texture->Unbind();
}