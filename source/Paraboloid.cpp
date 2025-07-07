#include "../include/Paraboloid.hpp"

Paraboloid::Paraboloid(bool hasBottomCap, bool hasTopCap, float height, float radius, int slices, int stacks, const std::string texturePath, bool lightingEnabled, const char *vertexPath, const char *fragmentPath)
    : Shape(texturePath, lightingEnabled, vertexPath, fragmentPath), hasBottomCap(hasBottomCap), hasTopCap(hasTopCap), height(height), radius(radius), slices(slices), stacks(stacks)
{

    setup();
}

void Paraboloid::generateMesh(std::vector<float> &vertices, std::vector<GLuint> &indices)
{

    vertices.clear();
    indices.clear();

    // Gerar vértices
    for (int i = 0; i <= stacks; ++i)
    {
        float stackRatio = static_cast<float>(i) / stacks;
        float y = height * stackRatio;
        float currentRadius = radius * sqrtf(stackRatio);

        for (int j = 0; j <= slices; ++j)
        {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;

            float x = currentRadius * cosf(sliceAngle);
            float z = currentRadius * sinf(sliceAngle);

            // Posição
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Coordenadas de textura
            if (texture != nullptr)
            {
                vertices.push_back(static_cast<float>(j) / slices);
                vertices.push_back(stackRatio);
            }

            // Normais
            if (lightingEnabled)
            {
                float nx = 2.0f * x;
                float ny = -1.0f;
                float nz = 2.0f * z;
                float length = sqrtf(nx * nx + ny * ny + nz * nz);
                vertices.push_back(nx / length);
                vertices.push_back(ny / length);
                vertices.push_back(nz / length);
            }
        }
    }

    // Gerar índices para as faces laterais
    for (int i = 0; i < stacks; ++i)
    {
        for (int j = 0; j < slices; ++j)
        {
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

    unsigned int stride = 3;
    if (texture != nullptr)stride += 2;
    if (lightingEnabled)stride += 3;

    // Tampa inferior
    if (hasBottomCap)
    {
        int centerIndex = vertices.size() / stride;

        // Vértice central
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        if (texture != nullptr)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (lightingEnabled)
        {
            vertices.push_back(0.0f);
            vertices.push_back(-1.0f);
            vertices.push_back(0.0f);
        }

        for (int j = 0; j <= slices; ++j)
        {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;
            float x = radius * cosf(sliceAngle);
            float z = radius * sinf(sliceAngle);

            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(z);

            if (texture != nullptr)
            {
                vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
                vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
            }

            if (lightingEnabled)
            {
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
            }
        }

        for (int j = 0; j < slices; ++j)
        {
            indices.push_back(centerIndex);
            indices.push_back(centerIndex + j + 1);
            indices.push_back(centerIndex + j + 2);
        }
    }

    // Tampa superior
    if (hasTopCap)
    {
        int topBaseIndex = vertices.size() / stride;

        vertices.push_back(0.0f);
        vertices.push_back(height);
        vertices.push_back(0.0f);

        if (texture != nullptr)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (lightingEnabled)
        {
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
        }

        for (int j = 0; j <= slices; ++j)
        {
            float sliceAngle = 2.0f * M_PI * static_cast<float>(j) / slices;
            float x = radius * cosf(sliceAngle);
            float z = radius * sinf(sliceAngle);

            vertices.push_back(x);
            vertices.push_back(height);
            vertices.push_back(z);

            if (texture != nullptr)
            {
                vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
                vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
            }

            if (lightingEnabled)
            {
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
            }
        }

        for (int j = 0; j < slices; ++j)
        {
            indices.push_back(topBaseIndex);
            indices.push_back(topBaseIndex + j + 2);
            indices.push_back(topBaseIndex + j + 1);
        }
    }
}


void Paraboloid::setup()
{
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    generateMesh(vertices, indices);
    indexCount = indices.size();

    unsigned int stride = 3;
    if (texture != nullptr) stride += 2;
    if (lightingEnabled) stride += 3;

    vao.Bind();

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

void Paraboloid::desenhar()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}