#include "Object.h"

using namespace std;

Object::Object(vector<float> vertices, vector<float> colors) {}
Object::Object(const Object& other) : vertices(other.vertices), colors(other.colors) {}
Object::Object(Object&& other) noexcept : vertices(other.vertices), colors(other.colors) {}
Object::~Object() {}
Object& Object::operator=(const Object& other) { return (*this = move(Object(other))); }
Object& Object::operator=(Object&& other) noexcept {
	if(this == &other)
		return *this;
	vertices = other.vertices;
	colors = other.colors;
	return *this;
}
const std::vector<float>& Object::getVertices() const { return vertices; }
const std::vector<float>& Object::getColors() const { return colors; }