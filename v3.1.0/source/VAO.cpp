#include "../include/VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

void VAO::Bind() const {
    glBindVertexArray(ID);
}

void VAO::Unbind() const {
    glBindVertexArray(0);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}
