#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nor;
layout (location = 2) in vec3 col;
layout (location = 3) in vec2 tex;

out vec3 fragmentColor;

uniform mat4 MVP;

void main()
{
    fragmentColor = nor;

    gl_Position = MVP * vec4(pos,1);
}