// GLSL version
#version 150 core
// shader inputs
in vec2 in_Vertex;
in vec3 in_Color;
// ouput
out vec3 color;
void main() {
	// final position of the vertex
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
	// sending the color to the fragment shader
	color = in_Color;
}
