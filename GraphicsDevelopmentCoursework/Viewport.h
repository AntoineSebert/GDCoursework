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
				inline Viewport& operator=(const Viewport& other);
				Viewport& operator=(Viewport&& other) noexcept;
			// getters
				inline float getHeight() const noexcept;
				inline float getWidth() const noexcept;
				inline float getPosx() const noexcept;
				inline float getPosy() const noexcept;
				glm::mat4 getProjection() const noexcept;
				glm::mat4 getModelview() const noexcept;
			// other
				void call() const;
};