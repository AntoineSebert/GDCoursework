#pragma once

#pragma warning(push, 0) // disable warnings
#include <glm/glm.hpp>
#pragma warning(pop)
#include <GL/glew.h>

class Viewport {
	/* ATTRIBUTES */
		private:
			float posx, posy, width, height;
			glm::mat4 projection, modelview;
	/* MEMBERS */
		public:
			// constructors
				Viewport(glm::vec2 pos, glm::vec2 dimension, glm::mat4 projection, glm::mat4 modelview);
				Viewport(const Viewport& other);
				Viewport(Viewport&& other) noexcept;
			// destructor
				~Viewport() noexcept;
			// operators
				Viewport& operator=(const Viewport& other);
				Viewport& operator=(Viewport&& other) noexcept;
			// getters
				float getHeight();
				float getWidth();
				float getPosx();
				float getPosy();
				glm::mat4 getProjection();
				glm::mat4 getModelview();
			// other
				void call();
};