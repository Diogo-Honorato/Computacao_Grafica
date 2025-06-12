#include "../include/Cube.hpp"

static float cubeVertices[] = {
                            //Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f
};

static GLuint cubeIndices[] = {
    //front
    0,1,2,2,3,0,

    //Right
    1,5,6,6,2,1,

    //Back
    4,5,6,6,7,4,

    //Left
    4,0,3,3,7,4,

    //Up
    3,2,6,6,7,3,

    //Down
    4,5,1,1,0,4
};

Cube::Cube() 
    : Shape("../shader/basic_shaders/vertex/basic_cube.vs", 
            "../shader/basic_shaders/fragment/basic_cube.fs"){

    setup();
}

Cube::Cube(const char* vertexPath, const char* fragmentPath) 
    : Shape(vertexPath, fragmentPath){

    setup();
}

void Cube::setup(){
    
    vao.Bind();
    vbo = new VBO(cubeVertices,sizeof(cubeVertices));
    ebo = new EBO(cubeIndices,sizeof(cubeIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    vao.Unbind();
}


void Cube::desenhar() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES,(sizeof(cubeIndices)/sizeof(GLsizei)), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}