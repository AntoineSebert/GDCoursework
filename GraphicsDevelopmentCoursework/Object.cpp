#include "Object.h"

using namespace std;

// constructors
	Object::Object(const vector<float>& newVertices, const vector<float>& newcolors)
		: vertices(newVertices), colors(newcolors) {
		if(colors.empty())
			colors = vector(newVertices.size(), (float)0.9);
	}
	Object::Object(const Object& other) : vertices(other.vertices), colors(other.colors) {}
	Object::Object(Object&& other) noexcept : vertices(other.vertices), colors(other.colors) {}
// destructor
	Object::~Object() {}
// operators
	Object& Object::operator=(const Object& other) { return (*this = move(Object(other))); }
	Object& Object::operator=(Object&& other) noexcept {
		if(this == &other)
			return *this;

		vertices = other.vertices;
		colors = other.colors;

		return *this;
	}
// getters
	const vector<float>& Object::getVertices() const { return vertices; }
	const vector<float>& Object::getcolors() const { return colors; }
// setters
	bool Object::changeColor(const vector<float>& newColors) {
		if(newColors.size() != vertices.size())
			return false;
		colors = newColors;
		return true;
	}
// other
	void Object::draw(const shared_ptr<Viewport> viewport, const Shader& shader, const glm::mat4& matrix) {
		viewport->call();

		auto program_id = shader.getProgramID();

		// enable shader
		glUseProgram(program_id);

		// create vertexAttribArrays for color & vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
		glEnableVertexAttribArray(1);
		// sending the matrices
		glUniformMatrix4fv(glGetUniformLocation(program_id, "projection"), 1, GL_FALSE, value_ptr(viewport->getProjection()));
		glUniformMatrix4fv(glGetUniformLocation(program_id, "modelview"), 1, GL_FALSE,
			value_ptr(matrix == glm::mat4() ? viewport->getModelview() : matrix)
		);
		// send vertices and colors to the shader
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size() / 3);
		// a bit of cleaning
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// disable shader
		glUseProgram(0);
	}