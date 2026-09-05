#version 330 core

uniform vec3 idColor;
out vec4 FragColor;
void main() { FragColor = vec4(idColor, 1.0); }