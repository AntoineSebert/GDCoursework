#include "Painter.hpp"

using namespace std;

const string Painter::shadersPath = "../parts/Shaders/";

Painter::Painter() {}
Painter::Painter(const Painter& other) : data(other.data), colors(other.colors) {
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
}
Painter::Painter(Painter&& other) noexcept : data(other.data), colors(other.colors) {
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
}
Painter::~Painter() noexcept {}
Painter& Painter::operator=(const Painter& other) { return (*this = move(Painter(other))); }
Painter& Painter::operator=(Painter&& other) noexcept {
	if(this == &other)
		return *this;
	data = other.data;
	colors = other.colors;
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
	return *this;
}
vector<float*> Painter::getData() const { return data; }
vector<unique_ptr<Shader>>::const_iterator Painter::shadersEnd() const { return shaders.end(); }
vector<float*>::const_iterator Painter::colorsEnd() const { return colors.end(); }
void Painter::drawTriangles(float* vertices) {
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, *data.insert(data.end(), vertices));
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
void Painter::useColor(vector<float*>::const_iterator color) {
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, *color);
	glEnableVertexAttribArray(1);
}
vector<unique_ptr<Shader>>::const_iterator Painter::addShader(std::string sourceVertex, std::string sourceFragment) {
	unique_ptr<Shader> myShader = unique_ptr<Shader>(new Shader(shadersPath + sourceVertex, shadersPath + sourceFragment));
	if(myShader->load()) {
		shaders.push_back(move(myShader));
		return --shaders.end();
	}
	return shaders.end();
}
vector<float*>::const_iterator Painter::addColor(float* color) { return colors.insert(colors.begin(), color); }
