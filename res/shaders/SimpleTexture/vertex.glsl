#version 330 core

uniform mat4 u_Camera;
uniform mat4 u_ModelMatrix;

layout (location = 0) in vec3 VertPos;
layout (location = 3) in vec2 VertTexCoord;

out vec2 FragTexCoord;

void main() {
    // Pass some variables to the fragment shader
    FragTexCoord = VertTexCoord;
    
    // Apply all matrix transformations to vert
    gl_Position = u_Camera * u_ModelMatrix * vec4(VertPos,1);
}
