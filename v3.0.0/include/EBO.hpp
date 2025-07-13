#ifndef EBO_HPP
#define EBO_HPP

#include "../dep/glad/include/glad/glad.h"

class EBO {
private:
    GLuint ID;
public:
    EBO(const GLuint* indices, GLsizeiptr size);
    void Bind() const;
    void Unbind() const;
    ~EBO();
};

#endif