#include "../include/Pipe.hpp"

constexpr float PI = glm::pi<float>();

Pipe::Pipe(std::vector<glm::vec3> &pathPoints, float topRadius, float baseRadius, int slices,const std::string texturePath, bool lightingEnabled,const char *vertexPath, const char *fragmentPath)
    : Shape(texturePath,lightingEnabled,vertexPath, fragmentPath), pathPoints(pathPoints), topRadius(topRadius), baseRadius(baseRadius), slices(slices)
{

    setup();
}

std::vector<float> Pipe::buildUnitCircleVertices()
{
    float sliceStep = 2 * PI / slices;
    std::vector<float> unitCircleVertices;

    for (int i = 0; i <= slices; ++i)
    {
        float sliceAngle = i * sliceStep;
        unitCircleVertices.push_back(cos(sliceAngle)); // x
        unitCircleVertices.push_back(sin(sliceAngle)); // y
        unitCircleVertices.push_back(0);               // z
    }
    return unitCircleVertices;
}

void Pipe::generateMesh(std::vector<float> &vertices, std::vector<GLuint> &indices)
{
    if (pathPoints.size() < 2)
        return;

    vertices.clear();
    indices.clear();

    std::vector<float> unitCircle = buildUnitCircleVertices();
    int stacks = static_cast<int>(pathPoints.size());

    std::vector<glm::vec3> tangents;
    calculatePathTangents(pathPoints, tangents);

    for (int i = 0; i < stacks; ++i)
    {
        const glm::vec3 &point = pathPoints[i];
        const glm::vec3 &tangent = tangents[i];

        glm::vec3 normal, binormal;
        calculateFrenetFrame(tangent, normal, binormal);

        float radius = baseRadius + (float)i / (stacks - 1) * (topRadius - baseRadius);

        for (int j = 0; j <= slices; ++j)
        {
            float x = unitCircle[j * 3];
            float y = unitCircle[j * 3 + 1];

            glm::vec3 localPos = normal * (radius * x) + binormal * (radius * y);
            glm::vec3 worldPos = point + localPos;

            // Posição
            vertices.push_back(worldPos.x);
            vertices.push_back(worldPos.y);
            vertices.push_back(worldPos.z);

            // Textura
            if (texture != nullptr)
            {
                vertices.push_back(static_cast<float>(j) / slices);       // s
                vertices.push_back(static_cast<float>(i) / (stacks - 1)); // t
            }

            // Normal
            if (lightingEnabled)
            {
                glm::vec3 normalVec = glm::normalize(localPos);
                vertices.push_back(normalVec.x);
                vertices.push_back(normalVec.y);
                vertices.push_back(normalVec.z);
            }
        }
    }

    // Índices das laterais
    for (int i = 0; i < stacks - 1; ++i)
    {
        for (int j = 0; j < slices; ++j)
        {
            int k1 = i * (slices + 1) + j;
            int k2 = k1 + slices + 1;

            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }
    }

    // Base cap
    {
        const glm::vec3 &center = pathPoints.front();
        unsigned int stride = 3;
        if (texture != nullptr) stride += 2;
        if (lightingEnabled) stride += 3;

        unsigned int centerIndex = vertices.size() / stride;

        // Vértice central
        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(center.z);
        if (texture != nullptr)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }
        if (lightingEnabled)
        {
            glm::vec3 n = -tangents.front();
            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }

        glm::vec3 normal = -tangents.front();
        glm::vec3 binormal, dummy;
        calculateFrenetFrame(normal, binormal, dummy);

        for (int i = 0; i <= slices; ++i)
        {
            float x = unitCircle[i * 3];
            float y = unitCircle[i * 3 + 1];

            glm::vec3 localPos = binormal * (baseRadius * x) + dummy * (baseRadius * y);
            glm::vec3 worldPos = center + localPos;

            vertices.push_back(worldPos.x);
            vertices.push_back(worldPos.y);
            vertices.push_back(worldPos.z);

            if (texture != nullptr)
            {
                vertices.push_back(x * 0.5f + 0.5f);
                vertices.push_back(y * 0.5f + 0.5f);
            }

            if (lightingEnabled)
            {
                glm::vec3 n = -tangents.front();
                vertices.push_back(n.x);
                vertices.push_back(n.y);
                vertices.push_back(n.z);
            }
        }

        for (int i = 0, k = centerIndex + 1; i < slices; ++i, ++k)
        {
            indices.push_back(centerIndex);
            indices.push_back((i < slices - 1) ? k + 1 : centerIndex + 1);
            indices.push_back(k);
        }
    }

    // Top cap
    {
        const glm::vec3 &center = pathPoints.back();
        unsigned int stride = 3;
        if (texture != nullptr) stride += 2;
        if (lightingEnabled) stride += 3;

        unsigned int centerIndex = vertices.size() / stride;

        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(center.z);
        if (texture != nullptr)
        {
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);
        }
        if (lightingEnabled)
        {
            glm::vec3 n = tangents.back();
            vertices.push_back(n.x);
            vertices.push_back(n.y);
            vertices.push_back(n.z);
        }

        glm::vec3 normal = tangents.back();
        glm::vec3 binormal, dummy;
        calculateFrenetFrame(normal, binormal, dummy);

        for (int i = 0; i <= slices; ++i)
        {
            float x = unitCircle[i * 3];
            float y = unitCircle[i * 3 + 1];

            glm::vec3 localPos = binormal * (topRadius * x) + dummy * (topRadius * y);
            glm::vec3 worldPos = center + localPos;

            vertices.push_back(worldPos.x);
            vertices.push_back(worldPos.y);
            vertices.push_back(worldPos.z);

            if (texture != nullptr)
            {
                vertices.push_back(x * 0.5f + 0.5f);
                vertices.push_back(y * 0.5f + 0.5f);
            }

            if (lightingEnabled)
            {
                glm::vec3 n = tangents.back();
                vertices.push_back(n.x);
                vertices.push_back(n.y);
                vertices.push_back(n.z);
            }
        }

        for (int i = 0, k = centerIndex + 1; i < slices; ++i, ++k)
        {
            indices.push_back(centerIndex);
            indices.push_back(k);
            indices.push_back((i < slices - 1) ? k + 1 : centerIndex + 1);
        }
    }
}


void Pipe::calculatePathTangents(const std::vector<glm::vec3> &path, std::vector<glm::vec3> &tangents)
{
    tangents.resize(path.size());

    // First point uses forward difference
    tangents[0] = glm::normalize(path[1] - path[0]);

    // Middle points use central difference for smoother tangents
    for (size_t i = 1; i < path.size() - 1; ++i)
    {
        tangents[i] = glm::normalize(path[i + 1] - path[i - 1]);
    }

    // Last point uses backward difference
    tangents.back() = glm::normalize(path.back() - path[path.size() - 2]);
}

void Pipe::calculateFrenetFrame(const glm::vec3 &tangent, glm::vec3 &normal, glm::vec3 &binormal)
{
    // Arbitrary up vector - can be parameterized for different orientations
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    // If tangent is parallel to up, use a different reference vector
    if (glm::length(glm::cross(tangent, up)) < 0.0001f)
    {
        up = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    // Calculate binormal and normal
    binormal = glm::normalize(glm::cross(tangent, up));
    normal = glm::normalize(glm::cross(binormal, tangent));
}

std::vector<glm::vec3> Pipe::generateTorus(int segments, float radius){
    std::vector<glm::vec3> ringPoints;
    const float TWO_PI = 2.0f * M_PI;

    for (int i = 0; i <= segments; ++i) {
        float angle = i * TWO_PI / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        ringPoints.emplace_back(glm::vec3(x, 0.0f, z));
    }

    return ringPoints;
}

void Pipe::setup()
{
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    generateMesh(vertices, indices);
    indexCount = static_cast<GLsizei>(indices.size());

    unsigned int stride = 3;
    if (texture != nullptr) stride += 2;
    if (lightingEnabled) stride += 3;

    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    if (texture != nullptr)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled)
    {
        int offset = (texture != nullptr) ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}


void Pipe::desenhar()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}