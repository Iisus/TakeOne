#version 330
out vec4 fragColor;

in vec3 fragmentColor;
void main(){
    fragColor = vec4(fragmentColor, 1.0);
}