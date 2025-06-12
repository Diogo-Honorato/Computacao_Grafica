#version 330 core

layout(location = 0) in vec3 aPos;

uniform model


void main()
{
    gl_Position = model * vec4(aPos, 1.0);
}