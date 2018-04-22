#include "Painter.hpp"

using namespace std;

Painter::Painter() { }
Painter::Painter(Painter&& other) noexcept : data(other.data) { other.data.reset(); }
Painter::~Painter() noexcept {}
Painter& Painter::operator=(const Painter& other) {
	Painter tmp(other);			// re-use copy-constructor  
	*this = move(tmp);		// re-use move-assignment  
	return *this;
}
Painter& Painter::operator=(Painter&& other) noexcept {
	if(this == &other)
		return *this;
	data = other.data;
	other.data.reset();
	return *this;
}
shared_ptr<vector<points>> Painter::getDataPointer() const { return data; }

void Painter::drawTriangles(float* vertices) {
	glClear(GL_COLOR_BUFFER_BIT);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}