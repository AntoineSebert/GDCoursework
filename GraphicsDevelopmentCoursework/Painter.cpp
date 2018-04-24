#include "Painter.hpp"

using namespace std;

Painter::Painter() {}
Painter::Painter(const Painter& other) : data(other.data), shaders(other.shaders) {}
Painter::Painter(Painter&& other) noexcept : data(other.data), shaders(other.shaders) {}
Painter::~Painter() noexcept {}
Painter& Painter::operator=(const Painter& other) { return (*this = move(Painter(other))); }
Painter& Painter::operator=(Painter&& other) noexcept {
	if(this == &other)
		return *this;
	data = other.data;
	shaders = other.shaders;
	return *this;
}
vector<float*> Painter::getData() const { return data; }
vector<unique_ptr<Shader>> Painter::getShaders() const { return shaders; }
void Painter::drawTriangles(float* vertices) {
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, *data.insert(data.end(), vertices));
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
vector<unique_ptr<Shader>>::const_iterator Painter::addShader(std::string sourceVertex, std::string sourceFragment) const {
	unique_ptr<Shader> myShader = make_unique<Shader>(new Shader(sourceVertex, sourceFragment));
	//return (myShader->load() ? shaders.insert(shaders.end(), myShader) : shaders.end());
	return shaders.end();
}