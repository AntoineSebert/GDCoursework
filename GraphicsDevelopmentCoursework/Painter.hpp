#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Shader.h"

#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Painter {
	/* ATTRIBUTES */
		private:
			const static std::string shadersPath;
			std::vector<std::vector<float>> vertices;
			std::vector<std::unique_ptr<Shader>> shaders;
			unsigned int vertexAttribArrays;
			std::map<std::string, std::vector<float>> palette;
	/* MEMBERS */
		public:
			// constructors
				Painter();
				Painter(const Painter& other);
				Painter(Painter&& other) noexcept;
			// destructor
				~Painter() noexcept;
			// operators
				Painter& operator=(const Painter& other);
				Painter& operator=(Painter&& other) noexcept;
			// getters
				const std::vector<std::vector<float>> getData() const;
				const std::vector<float> getColor(std::string colorName) const;
				const std::unique_ptr<Shader>& getShader(size_t index);
				// the return type is `size_t`, because `unsigned int` may not be suficient to store container size
				size_t getShadersSize() const noexcept;
				//std::vector<float> getVertices() const;
			// adding elements to object
				// using `size_t` instead of `const_iterator` because pointers/iterators may be invalidated during the execution
				size_t addVertices(std::vector<float> newVertices);
				std::optional<size_t> addShader(std::string sourceVertex, std::string sourceFragment);
				bool addColor(std::string name, std::vector<float> color);
			// creating vertexattribarrays
				void useColor(std::string name);
				void useVertices(size_t index);
				[[maybe_unused]] void useColor(std::vector<float> colors);
				[[maybe_unused]] void useVertices(std::vector<float> vertices);
			// draw vertices
				void drawVertices(size_t index); // the parameter is not used for we actually draw only one element
			// cleaning
				void disableVertexAttribArrays();
};