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
			std::vector<std::vector<float>> verticesContainer;
			std::vector<std::unique_ptr<Shader>> shaders;
			const static std::string shadersPath;
			unsigned int vertexAttribArrays;
			std::map<std::string, std::vector<float>> palette;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					Painter();
				// copy constructor
					Painter(const Painter& other);
				// move constructor
					Painter(Painter&& other) noexcept;
			// destructor
				~Painter() noexcept;
			// operators
				// copy assignment operator
					Painter& operator=(const Painter& other);
				// move assignment operator
					Painter& operator=(Painter&& other) noexcept;
			// getters
				std::vector<std::vector<float>> getData() const;
				std::vector<float> getColor(std::string colorName) const;
				std::unique_ptr<Shader>& getShader(size_t index);
				// the return type is `size_t`, because `unsigned int` may not be suficient to store container size
				size_t getShadersSize() const noexcept;
				//std::vector<float> getVertices() const;
			// adding to object
				// using `unsigned int` instead of `const_iterators` because pointers/iterators can be invalidated during the execution
				size_t addVertices(std::vector<float> vertices);
				std::optional<size_t> addShader(std::string sourceVertex, std::string sourceFragment);
				bool addColor(std::string name, std::vector<float> color);
			// creating vertexattribarrays
				void useColor(std::string name);
				void useVertices(unsigned int index);
				void useColor(std::vector<float> colors);
				void useVertices(std::vector<float> vertices);
			// draw vertices
				void drawVertices(unsigned int index); // the parameter is not used for we actually draw only one element
			// cleaning
				void disableVertexAttribArrays();
};