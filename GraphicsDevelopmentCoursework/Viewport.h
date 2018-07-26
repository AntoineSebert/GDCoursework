#pragma once

#pragma warning(push, 0) // disable warnings
#include <glm/glm.hpp>
#pragma warning(pop)

class Viewport {
	/* ATTRIBUTES */
		private:
			unsigned int posx, posy, width, height;
			glm::mat4 projection, modelview;
	/* MEMBERS */
		public:
			// constructors
				Viewport(unsigned int posx, unsigned int posy, unsigned int width, unsigned int weight, glm::mat4 projection, glm::mat4 modelview);
				Viewport(const Viewport& other);
				Viewport(Viewport&& other) noexcept;
			// destructor
				~Viewport() noexcept;
			// operators
				Viewport& operator=(const Viewport& other);
				Viewport& operator=(Viewport&& other) noexcept;
			// getters
				unsigned int getHeight();
				unsigned int getWidth();
				glm::mat4 getProjection();
				glm::mat4 getModelview();
};