#ifndef VAO_HPP
#define VAO_HPP

#include "../dep/glad/include/glad/glad.h"

class VAO {
private:
    GLuint ID;
public:
    VAO();
    void Bind() const;
    void Unbind() const;
    ~VAO();
};

#endif