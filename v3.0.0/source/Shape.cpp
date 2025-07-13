#include "../include/Shape.hpp"

Shape::Shape(Mesh *mesh, Shader* shader, Texture *tex, bool lightingEnabled)
    :mesh(mesh), shader(shader), lightingEnabled(lightingEnabled) 
{
    if (tex) texture = tex;
    indexCount = static_cast<GLsizei>(mesh->indices.size());
    verticesCount = static_cast<GLsizei>(mesh->vertices.size());
    setupVAO();
}

Shader* Shape::getShader() {
    return shader;
}

Texture* Shape::getTexture() {
    return texture;
}

void Shape::setupVAO() {

    vao.Bind();
    mesh->bindBuffers();

    int stride = 3;
    if (texture) stride += 2;
    if (lightingEnabled) stride += 3;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (texture) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (lightingEnabled) {
        int offset = texture ? 5 : 3;
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    vao.Unbind();
}

void Shape::desenharElem() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Shape::desenharArrays() {
    vao.Bind();
    glDrawArrays(GL_TRIANGLES,0,verticesCount);
    vao.Unbind();
}

void Shape::desenharLine() {
    vao.Bind();
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}