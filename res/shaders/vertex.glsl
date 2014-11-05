#version 330 core
layout (location = 0) in vec3 vectorPosition_modelspace;

layout(location = 2) in vec3 vertexColor;

out vec3 fragmentColor;

uniform mat4 MVP;

void main()
{
    fragmentColor = vectorPosition_modelspace;

    gl_Position = MVP * vec4(vectorPosition_modelspace,1);
}