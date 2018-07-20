#include "Painter.hpp"

using namespace std;

const string Painter::shadersPath = "../parts/Shaders/";

Painter::Painter() : vertexAttribArrays(0) {}
Painter::Painter(const Painter& other)
	: verticesContainer(other.verticesContainer), vertexAttribArrays(other.vertexAttribArrays), palette(other.palette) {
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
}
Painter::Painter(Painter&& other) noexcept
	: verticesContainer(other.verticesContainer), vertexAttribArrays(other.vertexAttribArrays), palette(other.palette) {
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
}
Painter::~Painter() noexcept {}
Painter& Painter::operator=(const Painter& other) { return (*this = move(Painter(other))); }
Painter& Painter::operator=(Painter&& other) noexcept {
	if(this == &other)
		return *this;
	verticesContainer = other.verticesContainer;
	vertexAttribArrays = other.vertexAttribArrays;
	palette = other.palette;
	shaders.clear();
	for(const auto& element : other.shaders)
		shaders.emplace_back(element.get());
	return *this;
}
vector<vector<float>> Painter::getData() const { return verticesContainer; }
vector<float> Painter::getColor(string colorName) const { return palette.find(colorName)->second; }
unique_ptr<Shader>& Painter::getShader(size_t index) { return shaders.at(index); }
size_t Painter::getShadersSize() const noexcept { return shaders.size(); }
size_t Painter::addVertices(vector<float> vertices) {
	verticesContainer.push_back(vertices);
	return verticesContainer.size() - 1;
}
optional<size_t> Painter::addShader(string sourceVertex, string sourceFragment) {
	unique_ptr<Shader> myShader = unique_ptr<Shader>(new Shader(shadersPath + sourceVertex, shadersPath + sourceFragment));
	if(myShader->load()) {
		shaders.push_back(move(myShader));
		return optional<size_t>(shaders.size() - 1);
	}
	return optional<size_t>();
}
bool Painter::addColor(string name, vector<float> color) {
	if(palette.find(name) != palette.end())
		return false;
	// check if color is already present
	for(const auto& element : palette) {
		auto it = mismatch(element.second.begin(), element.second.end(), color.begin(), color.end());
		if(it.first == element.second.end() || it.second == color.end())
			return false;
	}
	palette.emplace(name, color);
	return true;
}
void Painter::useColor(string name) {
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, palette.at(name).data());
	glEnableVertexAttribArray(vertexAttribArrays);
	++vertexAttribArrays;
}
void Painter::useVertices(unsigned int index) {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, verticesContainer.at(index).data());
	glEnableVertexAttribArray(vertexAttribArrays);
	++vertexAttribArrays;
}
void Painter::drawVertices(unsigned int index) {
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Painter::disableVertexAttribArrays() {
	for(unsigned int i = 0; i < vertexAttribArrays - 1; ++i)
		glDisableVertexAttribArray(i);
	vertexAttribArrays = 0;
}