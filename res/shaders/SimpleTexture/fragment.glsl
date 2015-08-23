#version 330

uniform sampler2D u_Texture;

in vec2 FragTexCoord;

out vec4 FinalColor;

void main() {

	FinalColor = texture(u_Texture, FragTexCoord);
}
