#include "../include/Sphere.hpp"

Sphere::Sphere(float radius, int slices, int stacks, const char *vertexPath,const char *fragmentPath)
:Shape(vertexPath,fragmentPath), radius(radius),slices(slices), stacks(stacks){
    
    setup();
}

void Sphere::generateMesh(std::vector<float>& vertices, std::vector<GLuint>& indices)
{
    const float PI = acos(-1.0f);

    float x, y, z, xy;                           // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius; // normal
    float s, t;                                  // texCoord

    float sliceStep = 2 * PI / slices;
    float stackStep = PI / stacks;
    float sliceAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep; // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);      // r * cos(u)
        z = radius * sinf(stackAngle);       // r * sin(u)

        // add (slices+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= slices; ++j)
        {
            sliceAngle = j * sliceStep; // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sliceAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sliceAngle); // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            s = 1.0f - (float)j / slices;
            t = (float)i / stacks;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (slices + 1); // beginning of current stack
        k2 = k1 + slices + 1;  // beginning of next stack

        for (int j = 0; j < slices; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
        }
    }
}

void Sphere::setup(){

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    generateMesh(vertices,indices);

    indexCount = static_cast<GLsizei>(indices.size());

    vao.Bind();

    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture = new Texture("../texture/cinza.jpg", GL_TEXTURE_2D, GL_RGBA, true);

    vao.Unbind();
}

void Sphere::desenhar() {
    texture->Bind(GL_TEXTURE0);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
    texture->Unbind();
}
