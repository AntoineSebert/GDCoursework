// GLSL version
#version 150 core
// shader input
in vec2 in_Vertex;
void main() {
	// final vertex position
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
}
