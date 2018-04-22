// GLSL version
#version 150 core
// shader input
in vec3 color;
// ouput
out vec4 out_Color;
void main() {
	// final color of the pixel
	out_Color = vec4(color, 1.0);
}
