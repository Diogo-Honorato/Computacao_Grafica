#ifndef SHADER_HPP
#define SHADER_HPP

#include "../dep/glad/include/glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int shaderID;

    Shader(const char* vertexPath, const char* fragmentPath);

    ~Shader();
    
    void useShaders();

    unsigned int getShaderID();

private:

    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif