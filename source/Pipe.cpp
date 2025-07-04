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

    // Generate unit circle vertices once
    std::vector<float> unitCircle = buildUnitCircleVertices();
    int stacks = static_cast<int>(pathPoints.size());

    // Calculate tangents for each path point
    std::vector<glm::vec3> tangents;
    calculatePathTangents(pathPoints, tangents);

    // Generate side vertices
    for (int i = 0; i < stacks; ++i)
    {
        const glm::vec3 &point = pathPoints[i];
        const glm::vec3 &tangent = tangents[i];

        // Calculate local coordinate system
        glm::vec3 normal, binormal;
        calculateFrenetFrame(tangent, normal, binormal);

        // Calculate current radius (lerp between base and top)
        float radius = baseRadius + (float)i / (stacks - 1) * (topRadius - baseRadius);

        for (int j = 0; j <= slices; ++j)
        {
            // Get unit circle point
            float x = unitCircle[j * 3];
            float y = unitCircle[j * 3 + 1];

            // Calculate vertex position in local coordinates
            glm::vec3 localPos = normal * (radius * x) + binormal * (radius * y);
            glm::vec3 worldPos = point + localPos;

            // Add position (3 floats)
            vertices.push_back(worldPos.x);
            vertices.push_back(worldPos.y);
            vertices.push_back(worldPos.z);

            // Add texture coordinates (2 floats)
            vertices.push_back(static_cast<float>(j) / slices);       // U
            vertices.push_back(static_cast<float>(i) / (stacks - 1)); // V
        }
    }

    // Generate side indices
    for (int i = 0; i < stacks - 1; ++i)
    {
        for (int j = 0; j < slices; ++j)
        {
            int k1 = i * (slices + 1) + j;
            int k2 = k1 + slices + 1;

            // Two triangles per sector
            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }
    }


    // Generate base cap (first point in path)
    {
        const glm::vec3 &center = pathPoints.front();

        // Center point
        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(center.z);
        vertices.push_back(0.5f); // s
        vertices.push_back(0.5f); // t

        unsigned int baseVertexIndex = vertices.size() / 5 - 1;

        // Base ring
        glm::vec3 normal = -tangents.front(); // Base normal points opposite to path tangent
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
            vertices.push_back(x * 0.5f + 0.5f); // s
            vertices.push_back(y * 0.5f + 0.5f); // t
        }

        // Generate base cap indices
        for (int i = 0, k = baseVertexIndex + 1; i < slices; ++i, ++k)
        {
            if (i < slices - 1)
            {
                indices.push_back(baseVertexIndex);
                indices.push_back(k + 1);
                indices.push_back(k);
            }
            else // last triangle
            {
                indices.push_back(baseVertexIndex);
                indices.push_back(baseVertexIndex + 1);
                indices.push_back(k);
            }
        }
    }

    
    // Generate top cap (last point in path)
    {
        const glm::vec3 &center = pathPoints.back();

        // Center point
        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(center.z);
        vertices.push_back(0.5f); // s
        vertices.push_back(0.5f); // t

        unsigned int topVertexIndex = static_cast<unsigned int>(vertices.size() / 5 - 1);

        glm::vec3 normal = tangents.back(); // Top normal points along path tangent
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
            vertices.push_back(x * 0.5f + 0.5f); // s
            vertices.push_back(y * 0.5f + 0.5f); // t
        }

        // Generate top cap indices
        for (int i = 0, k = topVertexIndex + 1; i < slices; ++i, ++k)
        {
            if (i < slices - 1)
            {
                indices.push_back(topVertexIndex);
                indices.push_back(k);
                indices.push_back(k + 1);
            }
            else // last triangle
            {
                indices.push_back(topVertexIndex);
                indices.push_back(k);
                indices.push_back(topVertexIndex + 1);
            }
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

    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.Unbind();
}

void Pipe::desenhar()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}