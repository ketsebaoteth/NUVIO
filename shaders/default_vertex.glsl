#version 330 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec4 inColor;

out vec4 vertColor;

void main() {
    gl_Position = vec4(inPos, 1.0);
    vertColor = inColor;
}
