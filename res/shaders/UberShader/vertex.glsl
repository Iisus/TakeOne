
#version 330 core

uniform mat4 camera;
uniform mat4 ModelMatrix;

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
layout (location = 3) in vec2 vertTexCoord;

out vec3 fragPos;
out vec2 texcoord;
out vec3 normal;
out vec3 viewPos;

void main() {
    // Pass some variables to the fragment shader
    texcoord = vertTexCoord;
    normal = vertNormal;
    fragPos = vertPos;
    viewPos = -camera[3].xyz * mat3(camera);

    // Apply all matrix transformations to vert
    gl_Position = camera * ModelMatrix * vec4(vertPos,1);
}
