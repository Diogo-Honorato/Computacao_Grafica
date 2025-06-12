// Geração de esfera baseada no método de stacks/slices de Song Ho Ahn
// Fonte original: https://www.songho.ca/opengl/gl_sphere.html
// Código foi adaptado para meu projeto com modificações na estrutura de dados e lógica


#include "../include/Sphere.hpp"

Sphere::Sphere():Shape("../shader/basic_shaders/vertex/basic_sphere.vs","../shader/basic_shaders/fragment/basic_sphere.fs"){
    
    generateSphere(1.0f,36,18);
    setup();
}

Sphere::Sphere(float radius, int slices, int stacks, const char *vertexPath, const char *fragmentPath): Shape(vertexPath, fragmentPath)
{
    generateSphere(radius,slices,stacks);
    setup();
}

void Sphere::generateSphere(float radius, int slices, int stacks)
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

        // add (slices+1) verticeAttribs per stack
        // the first and last verticeAttribs have same position and normal, but different tex coords
        for (int j = 0; j <= slices; ++j)
        {
            sliceAngle = j * sliceStep; // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sliceAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sliceAngle); // r * cos(u) * sin(v)
            verticeAttribs.push_back(x);
            verticeAttribs.push_back(y);
            verticeAttribs.push_back(z);

            // vertex tex coord between [0, 1]
            // s = (float)j / slices;
            // t = (float)i / stacks;
            // verticeAttribs.push_back(s);
            // verticeAttribs.push_back(t);
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

    vao.Bind();

    vbo = new VBO(verticeAttribs.data(), verticeAttribs.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vao.Unbind();
}

void Sphere::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}
