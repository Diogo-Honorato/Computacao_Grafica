#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../dep/glad/include/glad/glad.h"
#include <string>

class Texture {
private:
    GLuint texID;
    GLenum type;

public:
    Texture(const std::string& imagePath, GLenum textureType = GL_TEXTURE_2D, GLenum format = GL_RGBA, bool flip = true);
    Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255, GLenum textureType = GL_TEXTURE_2D);
    
    ~Texture();
    void Bind(GLenum textureUnit = GL_TEXTURE0) const;
    void Unbind() const;

    GLuint getTexID() const;
    GLenum getType() const;
};

#endif
