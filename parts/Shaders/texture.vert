// GLSL version
#version 150 core
// shader inputs
in vec3 in_Vertex;
in vec2 in_TexCoord0;
// uniform
uniform mat4 projection;
uniform mat4 modelview;
// ouput
out vec2 textureCoord;
void main() {
	// final position of the vertex in 3D
	gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	// sending the coordinates of the texture to the fragment shader
	textureCoord = in_TexCoord0;
}
