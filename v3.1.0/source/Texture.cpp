#include "../include/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../dep/stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& imagePath, GLenum textureType, GLenum format, bool flip)
    : type(textureType) {
    glGenTextures(1, &texID);
    glBindTexture(type, texID);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (flip) stbi_set_flip_vertically_on_load(true);

    int wtexidth, height, nrChannels;
    unsigned char* data = stbi_load(imagePath.c_str(), &wtexidth, &height, &nrChannels, 0);
    
    if (data) {
        GLenum internalFormat = (nrChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D(type, 0, internalFormat, wtexidth, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);

    } else {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
    }

    stbi_image_free(data);

    glBindTexture(type, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &texID);
}


void Texture::Bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(type, texID);
}

void Texture::Unbind() const {
    glBindTexture(type, 0);
}

GLuint Texture::getTexID() const {
    return texID;
}

GLenum Texture::getType() const {
    return type;
}
