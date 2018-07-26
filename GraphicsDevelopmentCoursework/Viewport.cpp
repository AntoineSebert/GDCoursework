#include "Viewport.h"

// public
	// constructors
		Viewport::Viewport(
			unsigned int posx, unsigned int posy, unsigned int width, unsigned int weight, glm::mat4 projection, glm::mat4 modelview)
			: posx(posx), posy(posy), width(width), height(height), projection(projection), modelview(modelview) {}
		Viewport::Viewport(const Viewport& other) : posx(other.posx), posy(other.posy), width(other.width), height(other.height),
			projection(other.projection), modelview(other.modelview) {}
		Viewport::Viewport(Viewport && other) noexcept : posx(other.posx), posy(other.posy), width(other.width), height(other.height),
			projection(other.projection), modelview(other.modelview) {}
	// destructor
		Viewport::~Viewport() {}
	// operators
		Viewport& Viewport::operator=(const Viewport& other) { return (*this = std::move(Viewport(other))); }
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
		unsigned int Viewport::getHeight() { return height; }
		unsigned int Viewport::getWidth() { return width; }
		glm::mat4 Viewport::getProjection() { return projection; }
		glm::mat4 Viewport::getModelview() { return modelview; }