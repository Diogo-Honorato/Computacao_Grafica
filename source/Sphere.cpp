#include "../include/Sphere.hpp"

Sphere::Sphere(float radius, int slices, int stacks, const std::string texturePath ,bool lightingEnabled,const char *vertexPath,const char *fragmentPath)
:Shape(texturePath,lightingEnabled,vertexPath,fragmentPath), radius(radius),slices(slices), stacks(stacks){
    
    setup();
}

void Sphere::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices)
{
    const float PI = acos(-1.0f);

    float x, y, z, xy;
    float s, t;

    float sliceStep = 2 * PI / slices;
    float stackStep = PI / stacks;
    float sliceAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= slices; ++j)
        {
            sliceAngle = j * sliceStep;

            x = xy * cosf(sliceAngle);
            y = xy * sinf(sliceAngle);

            // posição
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // textura
            if (texture != nullptr)
            {
                s = 1.0f - (float)j / slices;
                t = (float)i / stacks;
                vertices.push_back(s);
                vertices.push_back(t);
            }

            // normal
            if (lightingEnabled)
            {
                glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
                vertices.push_back(normal.x);
                vertices.push_back(normal.y);
                vertices.push_back(normal.z);
            }
        }
    }

    // Indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (slices + 1);
        k2 = k1 + slices + 1;

        for (int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}


void Sphere::setup()
{
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

    if (texture != nullptr)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled)
    {
        int offset = (texture != nullptr) ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}


void Sphere::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
