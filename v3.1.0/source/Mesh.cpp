#include "../include/Mesh.hpp"

namespace
{
    constexpr float PI = 3.14159265359f;

    std::vector<float> buildUnitCircleVertices(int slices)
    {
        std::vector<float> circle;
        float step = 2.0f * PI / slices;
        for (int i = 0; i <= slices; ++i)
        {
            float angle = i * step;
            circle.push_back(std::cos(angle));
            circle.push_back(std::sin(angle));
            circle.push_back(0.0f);
        }
        return circle;
    }

    void calculatePathTangents(const std::vector<glm::vec3> &path, std::vector<glm::vec3> &tangents)
    {
        tangents.resize(path.size());
        tangents[0] = glm::normalize(path[1] - path[0]);
        for (size_t i = 1; i < path.size() - 1; ++i)
            tangents[i] = glm::normalize(path[i + 1] - path[i - 1]);
        tangents.back() = glm::normalize(path.back() - path[path.size() - 2]);
    }

    void calculateFrenetFrame(const glm::vec3 &tangent, glm::vec3 &normal, glm::vec3 &binormal)
    {
        glm::vec3 up = std::abs(glm::dot(tangent, glm::vec3(0, 1, 0))) > 0.99f ? glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0);
        binormal = glm::normalize(glm::cross(tangent, up));
        normal = glm::normalize(glm::cross(binormal, tangent));
    }

    void computeParallelFrames(const std::vector<glm::vec3> &pathPoints, const std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &binormals)
    {
        size_t n = pathPoints.size();
        normals.resize(n);
        binormals.resize(n);

        // Frame inicial
        glm::vec3 t0 = tangents[0];
        glm::vec3 up = std::abs(glm::dot(t0, glm::vec3(0, 1, 0))) > 0.99f ? glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0);
        binormals[0] = glm::normalize(glm::cross(t0, up));
        normals[0] = glm::normalize(glm::cross(binormals[0], t0));

        for (size_t i = 1; i < n; ++i)
        {
            glm::vec3 prevTangent = tangents[i - 1];
            glm::vec3 currTangent = tangents[i];

            glm::vec3 axis = glm::cross(prevTangent, currTangent);
            float cosTheta = glm::dot(prevTangent, currTangent);
            float angle = std::acos(glm::clamp(cosTheta, -1.0f, 1.0f));

            if (glm::length(axis) < 1e-6f)
            {
                // Tangente praticamente igual: reusa frame anterior
                normals[i] = normals[i - 1];
                binormals[i] = binormals[i - 1];
            }
            else
            {
                axis = glm::normalize(axis);
                glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, axis);
                normals[i] = glm::mat3(rot) * normals[i - 1];
                binormals[i] = glm::normalize(glm::cross(currTangent, normals[i]));
            }
        }
    }

}

Mesh::Mesh(const std::vector<float> &verts, const std::vector<GLuint> &inds,bool withTexture, bool withNormals)
    : vertices(verts), indices(inds), withTexture(withTexture), withNormals(withNormals){

    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));

    if (!indices.empty())
    {
        ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));
    }
    else
    {
        ebo = nullptr;
    }
}

Mesh::~Mesh()
{
    if (vbo)
        delete vbo;
    if (ebo)
        delete ebo;
}

void Mesh::bindBuffers() const
{
    vbo->Bind();
    if (ebo)
        ebo->Bind();
}

void Mesh::clearCPUData()
{
    vertices.clear();
    vertices.shrink_to_fit();
    indices.clear();
    indices.shrink_to_fit();
}

Mesh *Mesh::cubeMesh(bool withTex, bool withNormals)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    const float positions[8][3] = {
        {-0.5f, -0.5f, -0.5f}, // 0
        {0.5f, -0.5f, -0.5f},  // 1
        {0.5f, 0.5f, -0.5f},   // 2
        {-0.5f, 0.5f, -0.5f},  // 3
        {-0.5f, -0.5f, 0.5f},  // 4
        {0.5f, -0.5f, 0.5f},   // 5
        {0.5f, 0.5f, 0.5f},    // 6
        {-0.5f, 0.5f, 0.5f}    // 7
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

    const float normals[6][3] = {
        {0.0f, 0.0f, -1.0f}, // Back
        {0.0f, 0.0f, 1.0f},  // Front
        {1.0f, 0.0f, 0.0f},  // Right
        {-1.0f, 0.0f, 0.0f}, // Left
        {0.0f, 1.0f, 0.0f},  // Top
        {0.0f, -1.0f, 0.0f}  // Bottom
    };

    int start = 3;

    if (withTex) start += 2;
    if (withNormals) start += 3;

    for (int i = 0; i < 6; ++i)
    {

        int startIndex = vertices.size() / start;

        for (int j = 0; j < 4; ++j)
        {
            int posIdx = faces[i][j];

            vertices.push_back(positions[posIdx][0]); // x
            vertices.push_back(positions[posIdx][1]); // y
            vertices.push_back(positions[posIdx][2]); // z

            if (withTex)
            {
                vertices.push_back(texCoords[j][0]); // u
                vertices.push_back(texCoords[j][1]); // v
            }

            if (withNormals)
            {
                vertices.push_back(normals[i][0]);
                vertices.push_back(normals[i][1]);
                vertices.push_back(normals[i][2]);
            }
        }

        indices.push_back(startIndex);
        indices.push_back(startIndex + 1);
        indices.push_back(startIndex + 2);
        indices.push_back(startIndex + 2);
        indices.push_back(startIndex + 3);
        indices.push_back(startIndex);
    }

    return new Mesh(vertices, indices, withTex, withNormals);
}

Mesh *Mesh::axialExtruderMesh(bool withTexture, bool withNormals, bool hasBottomCap, bool hasTopCap, float baseRadius, float topRadius, float height, int slices, int stacks)
{
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    const float PI = acos(-1.0f);
    float sliceStep = 2 * PI / slices;
    float z, x, y, radius;

    std::vector<float> unitCircleVertices;
    for (int i = 0; i <= slices; ++i)
    {
        float angle = i * sliceStep;
        unitCircleVertices.push_back(cos(angle));
        unitCircleVertices.push_back(sin(angle));
        unitCircleVertices.push_back(0);
    }

    // Corpo lateral
    for (int i = 0; i <= stacks; ++i)
    {
        z = -height / 2.0f + (float)i / stacks * height;
        radius = baseRadius + (float)i / stacks * (topRadius - baseRadius);
        float t = (float)i / stacks;

        for (int j = 0, k = 0; j <= slices; ++j, k += 3)
        {
            x = unitCircleVertices[k];
            y = unitCircleVertices[k + 1];

            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z);

            if (withTexture)
            {
                vertices.push_back(1.0f - (float)j / slices);
                vertices.push_back(t);
            }

            if (withNormals)
            {
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(0);
            }
        }
    }

    int stride = 3 + (withTexture ? 2 : 0) + (withNormals ? 3 : 0);

    // Indices laterais
    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (slices + 1);
        int k2 = k1 + slices + 1;

        for (int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }
    }

    // Base inferior
    if (hasBottomCap)
    {
        int baseCenterIndex = vertices.size() / stride;
        z = -height / 2.0f;

        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(z);

        if (withTexture)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (withNormals)
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

            if (withTexture)
            {
                vertices.push_back(-x * 0.5f + 0.5f);
                vertices.push_back(-y * 0.5f + 0.5f);
            }

            if (withNormals)
            {
                vertices.push_back(0);
                vertices.push_back(0);
                vertices.push_back(-1);
            }
        }

        for (int i = 0, k = baseCenterIndex + 1; i < slices; ++i, ++k)
        {
            if (i < slices - 1)
            {
                indices.push_back(baseCenterIndex);
                indices.push_back(k + 1);
                indices.push_back(k);
            }
            else
            {
                indices.push_back(baseCenterIndex);
                indices.push_back(baseCenterIndex + 1);
                indices.push_back(k);
            }
        }
    }

    // Base superior
    if (hasTopCap)
    {
        int topCenterIndex = vertices.size() / stride;
        z = height / 2.0f;

        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(z);

        if (withTexture)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (withNormals)
        {
            vertices.push_back(0);
            vertices.push_back(0);
            vertices.push_back(1);
        }

        for (int i = 0, j = 0; i < slices; ++i, j += 3)
        {
            x = unitCircleVertices[j];
            y = unitCircleVertices[j + 1];

            vertices.push_back(x * topRadius);
            vertices.push_back(y * topRadius);
            vertices.push_back(z);

            if (withTexture)
            {
                vertices.push_back(x * 0.5f + 0.5f);
                vertices.push_back(-y * 0.5f + 0.5f);
            }

            if (withNormals)
            {
                vertices.push_back(0);
                vertices.push_back(0);
                vertices.push_back(1);
            }
        }

        for (int i = 0, k = topCenterIndex + 1; i < slices; ++i, ++k)
        {
            if (i < slices - 1)
            {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(k + 1);
            }
            else
            {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(topCenterIndex + 1);
            }
        }
    }

    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::circleMesh(bool withTexture, bool withNormals, float radius, int segments)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    // Centro do círculo
    vertices.push_back(0.0f); // x
    vertices.push_back(0.0f); // y
    vertices.push_back(0.0f); // z

    if (withTexture)
    {
        vertices.push_back(0.5f); // s
        vertices.push_back(0.5f); // t
    }

    if (withNormals)
    {
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
    }

    for (int i = 0; i <= segments; ++i)
    {
        float angle = i * 2.0f * M_PI / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Posição
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        // textura
        if (withTexture)
        {
            float s = 0.5f + 0.5f * cos(angle);
            float t = 0.5f + 0.5f * sin(angle);
            vertices.push_back(s);
            vertices.push_back(t);
        }

        // Normal
        if (withNormals)
        {
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
        }

        // indices
        if (i > 0)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
    }
    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::lineMesh(std::vector<float> &pointsRef, std::vector<GLuint> &indicesRef)
{

    return new Mesh(pointsRef, indicesRef,false,false);
}

Mesh *Mesh::paraboloidMesh(bool withTexture, bool withNormals, bool hasBottomCap, bool hasTopCap, float height, float radius, int slices, int stacks)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

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
            if (withTexture)
            {
                vertices.push_back(static_cast<float>(j) / slices);
                vertices.push_back(stackRatio);
            }

            // Normais
            if (withNormals)
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
    if (withTexture)
        stride += 2;
    if (withNormals)
        stride += 3;

    // Tampa inferior
    if (hasBottomCap)
    {
        int centerIndex = vertices.size() / stride;

        // Vértice central
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        if (withTexture)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (withNormals)
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

            if (withTexture)
            {
                vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
                vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
            }

            if (withNormals)
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

        if (withTexture)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }

        if (withNormals)
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

            if (withTexture)
            {
                vertices.push_back(0.5f + 0.5f * cosf(sliceAngle));
                vertices.push_back(0.5f + 0.5f * sinf(sliceAngle));
            }

            if (withNormals)
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

    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::pipeMesh(std::vector<glm::vec3> &pathPoints, bool withTexture, bool withNormals, bool hasBottomCap, bool hasTopCap, float topRadius, float baseRadius, int slices)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;
    if (pathPoints.size() < 2)
        return new Mesh(vertices, indices,withTexture, withNormals);

    auto unitCircle = buildUnitCircleVertices(slices);
    int stacks = static_cast<int>(pathPoints.size());
    auto stride = 3 + (withTexture ? 2 : 0) + (withNormals ? 3 : 0);

    std::vector<glm::vec3> tangents,normals, binormals;
    calculatePathTangents(pathPoints, tangents);
    computeParallelFrames(pathPoints, tangents, normals, binormals);
    
    for (int i = 0; i < stacks; ++i)
    {
        glm::vec3 point = pathPoints[i];
        glm::vec3 normal = normals[i];
        glm::vec3 binormal = binormals[i];

        float radius = baseRadius + (float)i / (stacks - 1) * (topRadius - baseRadius);

        for (int j = 0; j <= slices; ++j)
        {
            float x = unitCircle[j * 3];
            float y = unitCircle[j * 3 + 1];

            glm::vec3 local = normal * (radius * x) + binormal * (radius * y);
            glm::vec3 world = point + local;

            vertices.insert(vertices.end(), {world.x, world.y, world.z});
            if (withTexture)
            {
                vertices.push_back((float)j / slices);
                vertices.push_back((float)i / (stacks - 1));
            }
            if (withNormals)
            {
                glm::vec3 n = glm::normalize(local);
                vertices.insert(vertices.end(), {n.x, n.y, n.z});
            }
        }
    }

    for (GLuint i = 0; i < stacks - 1; ++i)
    {
        for (GLuint j = 0; j < slices; ++j)
        {
            GLuint k1 = i * (slices + 1) + j;
            GLuint k2 = k1 + slices + 1;

            indices.insert(indices.end(), {k1, k1 + 1, k2});
            indices.insert(indices.end(), {k2, k1 + 1, k2 + 1});
        }
    }

    auto addCap = [&](bool isTop)
    {
        const glm::vec3 &center = isTop ? pathPoints.back() : pathPoints.front();
        glm::vec3 normal = isTop ? tangents.back() : -tangents.front();
        glm::vec3 b, d;
        calculateFrenetFrame(normal, b, d);
        float radius = isTop ? topRadius : baseRadius;
        int centerIndex = vertices.size() / stride;

        vertices.insert(vertices.end(), {center.x, center.y, center.z});
        if (withTexture)
            vertices.insert(vertices.end(), {0.5f, 0.5f});
        if (withNormals)
            vertices.insert(vertices.end(), {normal.x, normal.y, normal.z});

        for (int i = 0; i <= slices; ++i)
        {
            float x = unitCircle[i * 3];
            float y = unitCircle[i * 3 + 1];
            glm::vec3 pos = center + b * (radius * x) + d * (radius * y);
            vertices.insert(vertices.end(), {pos.x, pos.y, pos.z});
            if (withTexture)
                vertices.insert(vertices.end(), {x * 0.5f + 0.5f, y * 0.5f + 0.5f});
            if (withNormals)
                vertices.insert(vertices.end(), {normal.x, normal.y, normal.z});
        }

        for (int i = 0, k = centerIndex + 1; i < slices; ++i, ++k)
        {
            indices.push_back(centerIndex);
            indices.push_back(isTop ? k : (i < slices - 1 ? k + 1 : centerIndex + 1));
            indices.push_back(isTop ? (i < slices - 1 ? k + 1 : centerIndex + 1) : k);
        }
    };

    if (hasBottomCap)
        addCap(false);
    if (hasTopCap)
        addCap(true);

    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::sphereMesh(bool withTexture, bool withNormals, float radius, int slices, int stacks)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

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
            if (withTexture)
            {
                s = 1.0f - (float)j / slices;
                t = (float)i / stacks;
                vertices.push_back(s);
                vertices.push_back(t);
            }

            // normal
            if (withNormals)
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

    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::squareMesh(bool withTexture, bool withNormals)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {-0.5f, 0.5f, 0.0f}};

    // Coordenadas de textura (s, t)
    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}};

    // Normal para todos os vértices
    glm::vec3 normal(1.0f, 1.0f, 0.0f);

    vertices.clear();
    for (int i = 0; i < 4; ++i)
    {
        // Posição
        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);

        // Textura
        if (withTexture)
        {
            vertices.push_back(texCoords[i].x);
            vertices.push_back(texCoords[i].y);
        }

        // Normal
        if (withNormals)
        {
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    indices = {
        0, 1, 2,
        2, 3, 0};

    return new Mesh(vertices, indices,withTexture, withNormals);
}

Mesh *Mesh::triangleMesh(bool withTexture, bool withNormals)
{

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    // Posições dos vértices
    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}};

    // Coordenadas de textura
    std::vector<glm::vec2> texCoords = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {0.5f, 1.0f}};

    glm::vec3 normal(1.0f, 1.0f, 0.0f);

    vertices.clear();
    for (int i = 0; i < 3; ++i)
    {
        // posição
        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);

        // textura
        if (withTexture)
        {
            vertices.push_back(texCoords[i].x);
            vertices.push_back(texCoords[i].y);
        }

        // normal
        if (withNormals)
        {
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    indices = {0, 1, 2};

    return new Mesh(vertices, indices,withTexture, withNormals);
}