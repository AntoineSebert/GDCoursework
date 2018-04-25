// GLSL version
#version 150 core
// shader input
in vec2 textureCoord;
// uniform
uniform sampler2D texture;
// ouput
out vec4 out_Color;
void main() {
	// color of the pixel
	out_Color = texture(texture, textureCoord);
}
