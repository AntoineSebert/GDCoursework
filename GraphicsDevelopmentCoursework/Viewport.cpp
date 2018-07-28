#include "Viewport.h"

using namespace glm;
using namespace std;

// constructors
	Viewport::Viewport(glm::vec2 pos, glm::vec2 dimension, glm::mat4 projection, glm::mat4 modelview) : posx(pos.x), posy(pos.y),
		width(dimension.x), height(dimension.y), projection(projection), modelview(modelview) {}
	Viewport::Viewport(const Viewport& other) : posx(other.posx), posy(other.posy), width(other.width), height(other.height),
		projection(other.projection), modelview(other.modelview) {}
	Viewport::Viewport(Viewport && other) noexcept : posx(other.posx), posy(other.posy), width(other.width), height(other.height),
		projection(other.projection), modelview(other.modelview) {}
// destructor
	Viewport::~Viewport() {}
// operators
	Viewport& Viewport::operator=(const Viewport& other) { return (*this = move(Viewport(other))); }
	Viewport& Viewport::operator=(Viewport&& other) noexcept {
		if(this == &other)
			return *this;

		posx = other.posx;
		posy = other.posy;
		projection = other.projection;
		modelview = other.modelview;

		return *this;
	}
// getters
	float Viewport::getHeight() const noexcept { return height; }
	float Viewport::getWidth() const noexcept { return width; }
	float Viewport::getPosx() const noexcept { return posx; }
	float Viewport::getPosy() const noexcept { return posy; }
	mat4 Viewport::getProjection() const noexcept { return projection; }
	mat4 Viewport::getModelview() const noexcept { return modelview; }
// other
	void Viewport::call() const { glViewport(posx, posy, (GLsizei)width, (GLsizei)height);  }
