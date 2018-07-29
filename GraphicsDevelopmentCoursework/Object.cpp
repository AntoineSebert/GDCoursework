#include "Object.h"

using namespace std;

std::weak_ptr<Viewport> Object::last_used_viewport;

// constructors
	Object::Object(const vector<float>& newVertices, const vector<float>& newColors)
		: vertices(newVertices), colors(newColors) {}
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
	const vector<float>& Object::getColors() const { return colors; }
// setters
	bool Object::changeColor(const vector<float>& newColor) {
		if(newColor.size() != vertices.size())
			return false;
		colors = newColor;
		return true;
	}
// other
	bool Object::draw(const shared_ptr<Viewport> viewport, const Shader& shader, const glm::mat4& matrix) {
		if(viewport != last_used_viewport.lock())
			last_used_viewport = weak_ptr<Viewport>(viewport);
		viewport->call();

		auto program_id = shader.getProgramID();

		// enable shader
		glUseProgram(program_id);

		// create vertexAttribArrays for color & vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);
		if(colors.empty())
			colors = vector<float>(vertices.size(), 0.9);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
		glEnableVertexAttribArray(1);
		// sending the matrices
		glUniformMatrix4fv(glGetUniformLocation(program_id, "projection"), 1, GL_FALSE, value_ptr(viewport->getProjection()));
		glUniformMatrix4fv(glGetUniformLocation(program_id, "modelview"), 1, GL_FALSE,
			value_ptr(matrix == glm::mat4() ? viewport->getModelview() : matrix)
		);
		// send vertices and colors to the shader
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		// a bit of cleaning
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// disable shader
		glUseProgram(0);

		return false;
	}