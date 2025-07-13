#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "VBO.hpp"
#include "EBO.hpp"
#include "../dep/glm/glm.hpp"
#include "../dep/glm/gtc/matrix_transform.hpp"

class Mesh {
public:
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    VBO* vbo = nullptr;
    EBO* ebo = nullptr;

    Mesh(const std::vector<float>& verts, const std::vector<GLuint>& inds);
    ~Mesh();

    void bindBuffers() const;
    void clearCPUData();

    static Mesh* cubeMesh(bool withTexture =false, bool withNormals = false);

    static Mesh* axialExtruderMesh(bool withTexture = false,bool withNormals = false,bool hasBottomCap = false,bool hasTopCap = false,float baseRadius = 1.0f,float topRadius = 1.0f,float height = 2.0f,int slices = 36,int stacks = 8);

    static Mesh* circleMesh(bool withTexture = false,bool withNormals = false,float radius = 0.5f, int segments = 30);
    
    static Mesh* lineMesh(std::vector<float>& pointsRef, std::vector<GLuint>& indicesRef);
    
    static Mesh* paraboloidMesh(bool withTexture = false,bool withNormals = false,bool hasBottomCap = false,bool hasTopCap = false,float height = 1.0f,float radius = 1.0f, int slices = 36, int stacks = 18);
    
    static Mesh* pipeMesh(std::vector<glm::vec3>& pathPoints,bool withTexture = false,bool withNormals = false,bool hasBottomCap = false,bool hasTopCap = false,float topRadius=0.5f,float baseRadius=0.5f,int slices = 16);
    
    static Mesh* sphereMesh(bool withTexture = false,bool withNormals = false,float radius = 1.0f, int slices = 36, int stacks = 18);
    
    static Mesh* squareMesh(bool withTexture = false,bool withNormals = false);
    
    static Mesh* triangleMesh(bool withTexture = false,bool withNormals = false);
};


#endif