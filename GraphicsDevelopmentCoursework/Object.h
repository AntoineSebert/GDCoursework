#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#pragma warning(push, 0) // disable warnings
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "Shader.h"
#include "Viewport.h"

class Object {
	/* ATTRIBUTES */
		private:
			std::vector<float> vertices;
			std::vector<float> colors;
	/* MEMBERS */
		public:
			// constructors
				Object(const std::vector<float>& newVertices, const std::vector<float>& newcolors = std::vector<float>());
				Object(const Object& other);
				Object(Object&& other) noexcept;
			// destructor
				~Object() noexcept;
			// operators
				inline Object& operator=(const Object& other);
				Object& operator=(Object&& other) noexcept;
			// getters
				// thou shalt not modify these objects
				inline const std::vector<float>& getVertices() const;
				inline const std::vector<float>& getcolors() const;
			// setters
				bool changeColor(const std::vector<float>& newColors);
			// other
				bool draw(const std::shared_ptr<Viewport> viewport, const Shader& shader, const glm::mat4& matrix = glm::mat4());
};