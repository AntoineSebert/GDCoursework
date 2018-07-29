#include "Object.h"

using namespace std;

std::weak_ptr<Viewport> Object::last_used_viewport;
unsigned int Object::vertexAttribArrays = 0;

// constructors
	Object::Object(const vector<float>& newVertices, const vector<float>& newColors, string sourceVertex, string sourceFragment)
		: vertices(newVertices), colors(newColors), shader(Shader(sourceVertex, sourceFragment)) {}
	Object::Object(const Object& other) : vertices(other.vertices), colors(other.colors), shader(other.shader) {}
	Object::Object(Object&& other) noexcept : vertices(other.vertices), colors(other.colors), shader(other.shader) {}
// destructor
	Object::~Object() { vertexAttribArrays -= 2; }
// operators
	Object& Object::operator=(const Object& other) { return (*this = move(Object(other))); }
	Object& Object::operator=(Object&& other) noexcept {
		if(this == &other)
			return *this;

		vertices = other.vertices;
		colors = other.colors;
		shader = other.shader;

		return *this;
	}
// getters
	const vector<float>& Object::getVertices() const { return vertices; }
	const vector<float>& Object::getColors() const { return colors; }
// other
	bool Object::draw(const shared_ptr<Viewport> viewport) {
		if(viewport != last_used_viewport.lock())
			last_used_viewport = weak_ptr<Viewport>(viewport);
		viewport->call();

		shader.load();

		auto program_id = shader.getProgramID();

		// enable shader
		glUseProgram(program_id);

		// create vertexAttribArrays for color & vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glEnableVertexAttribArray(0);
		++vertexAttribArrays;
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
		glEnableVertexAttribArray(1);
		++vertexAttribArrays;
		// sending the matrices
		glUniformMatrix4fv(glGetUniformLocation(program_id, "projection"), 1, GL_FALSE, value_ptr(viewport->getProjection()));
		glUniformMatrix4fv(glGetUniformLocation(program_id, "modelview"), 1, GL_FALSE, value_ptr(viewport->getModelview()));
		// send vertices and colors to the shader
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// a bit of cleaning
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// disable shader
		glUseProgram(0);

		return false;
	}