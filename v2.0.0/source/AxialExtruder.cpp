#include "../include/AxialExtruder.hpp"

AxialExtruder::AxialExtruder(float topRadius, float baseRadius, float height, int slices, int stacks, const std::string texturePath, bool lightingEnabled, const char *vertexPath, const char *fragmentPath)
: Shape(texturePath, lightingEnabled, vertexPath, fragmentPath), baseRadius(baseRadius), topRadius(topRadius), height(height), slices(slices),stacks(stacks)
{
    setup();
}
std::vector<float> AxialExtruder::buildUnitCircleVertices()
{

    const float PI = acos(-1.0f);
    float sliceStep = 2 * PI / slices;
    float sliceAngle; // radian

    std::vector<float> unitCircleVertices;

    for (int i = 0; i <= slices; ++i)
    {
        sliceAngle = i * sliceStep;
        unitCircleVertices.push_back(cos(sliceAngle)); // x
        unitCircleVertices.push_back(sin(sliceAngle)); // y
        unitCircleVertices.push_back(0);               // z
    }

    return unitCircleVertices;
}

void AxialExtruder::generateMesh(std::vector<float> &vertices, std::vector<GLuint> &indices)
{

    float x, y, z; // vertex position
    float s, t;    // texCoord
    float radius;  // radius for each stack

    std::vector<float> unitCircleVertices = buildUnitCircleVertices();

    // put vertices of side cylinder to array by scaling unit circle
    for (int i = 0; i <= stacks; ++i)
    {
        z = -(height * 0.5f) + (float)i / stacks * height;                  // vertex position z
        radius = baseRadius + (float)i / stacks * (topRadius - baseRadius); // lerp
        float t = (float)i / stacks;                                        // top-to-bottom

        for (int j = 0, k = 0; j <= slices; ++j, k += 3)
        {
            x = unitCircleVertices[k];
            y = unitCircleVertices[k + 1];

            // positions
            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z);

            // textures
            if (texture != nullptr)
            {
                vertices.push_back(1.0f - (float)j / slices);
                vertices.push_back(t);
            }

            // normals
            if (lightingEnabled)
            {
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(unitCircleVertices[k + 2]);
            }
        }
    }

    unsigned int stride = 3;

    if (texture != nullptr)stride += 2;
    if (lightingEnabled)stride += 3;

    unsigned int baseVertexIndex = (unsigned int)(vertices.size() / stride);

    //Base
    z = -height * 0.5f;

    // centro
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(z);

    if (texture != nullptr)
    {
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);
    }

    if (lightingEnabled)
    {
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(-1);
    }

    for (int i = 0, j = 0; i < slices; ++i, j += 3)
    {
        x = unitCircleVertices[j];
        y = unitCircleVertices[j + 1];

        vertices.push_back(x * baseRadius);
        vertices.push_back(y * baseRadius);
        vertices.push_back(z);

        if (texture != nullptr)
        {
            vertices.push_back(-x * 0.5f + 0.5f);
            vertices.push_back(-y * 0.5f + 0.5f);
        }

        if (lightingEnabled)
        {
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(-1);
        }
    }

    unsigned int topVertexIndex = (unsigned int)(vertices.size() / stride);

    //Top
    z = height * 0.5f;

    // centro
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(z);

    if (texture != nullptr)
    {
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);
    }

    if (lightingEnabled)
    {
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(1); // normal para cima
    }

    for (int i = 0, j = 0; i < slices; ++i, j += 3)
    {
        x = unitCircleVertices[j];
        y = unitCircleVertices[j + 1];

        vertices.push_back(x * topRadius);
        vertices.push_back(y * topRadius);
        vertices.push_back(z);

        if (texture != nullptr)
        {
            vertices.push_back(x * 0.5f + 0.5f);
            vertices.push_back(-y * 0.5f + 0.5f);
        }

        if (lightingEnabled)
        {
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(1);
        }
    }

    // put indices for sides
    unsigned int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (slices + 1); // bebinning of current stack
        k2 = k1 + slices + 1;  // beginning of next stack

        for (int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            // 2 trianles per sector
            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }
    }

    // put indices for base
    for (int i = 0, k = baseVertexIndex + 1; i < slices; ++i, ++k)
    {
        if (i < (slices - 1))
        {

            indices.push_back(baseVertexIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else
        { // last triangle

            indices.push_back(baseVertexIndex);
            indices.push_back(baseVertexIndex + 1);
            indices.push_back(k);
        }
    }

    for (int i = 0, k = topVertexIndex + 1; i < slices; ++i, ++k)
    {
        if (i < (slices - 1))
        {

            indices.push_back(topVertexIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else
        {

            indices.push_back(topVertexIndex);
            indices.push_back(k);
            indices.push_back(topVertexIndex + 1);
        }
    }
}

void AxialExtruder::setup()
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    generateMesh(vertices, indices);

    indexCount = static_cast<GLsizei>(indices.size());

    int stride = 3;

    if (texture != nullptr) stride += 2;
    if (lightingEnabled)stride += 3;

    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(vertices[0]));
    ebo = new EBO(indices.data(), indices.size() * sizeof(indices[0]));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    if (texture != nullptr)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled)
    {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}

void AxialExtruder::desenhar()
{

    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}