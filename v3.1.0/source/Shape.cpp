#include "../include/Shape.hpp"

Shape::Shape(Mesh *mesh, GLenum drawMode, bool textureEnabled,bool lightingEnabled)
    :mesh(mesh), drawMode(drawMode),textureEnabled(textureEnabled),lightingEnabled(lightingEnabled) 
{
    indexCount = static_cast<GLsizei>(mesh->indices.size());
    verticesCount = static_cast<GLsizei>(mesh->vertices.size());
    setupVAO();
}

void Shape::setupVAO() {

    vao.Bind();
    mesh->bindBuffers();

    int stride = 3;
    if (mesh->withTexture) stride += 2;
    if (mesh->withNormals) stride += 3;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (textureEnabled) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled) {
        int offset = mesh->withTexture ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}

void Shape::drawObject() {
    
    vao.Bind();
    glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}