// GLSL version
#version 150 core
// shader inputs
in vec3 in_Vertex;
in vec3 in_Color;
// uniform
uniform mat4 projection;
uniform mat4 modelview;
// ouput
out vec3 color;
void main() {
	// final position of the vertex in 3D
	gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	// sending the color to the fragment shader
	color = in_Color;
}
