#ifndef VBO_HPP
#define VBO_HPP

#include "../dep/glad/include/glad/glad.h"

class VBO {
private:
    GLuint ID;
public:
    VBO(const float* data, GLsizeiptr size);
    void Bind() const;
    void Unbind() const;
    ~VBO();
};

#endif