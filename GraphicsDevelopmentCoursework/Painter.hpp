#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Shader.h"

#include <memory>
#include <utility>
#include <vector>

class Painter {
	/* ATTRIBUTES */
		private:
			std::vector<float*> data;
			std::vector<float*> colors;
			std::vector<std::unique_ptr<Shader>> shaders;
			const static std::string shadersPath;
			unsigned int vertexAttribArrays;
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
				std::vector<float*> getData() const;
				std::vector<std::unique_ptr<Shader>>::const_iterator shadersEnd() const;
				std::vector<float*>::const_iterator colorsEnd() const;
			// adding to object
				std::vector<float*>::const_iterator addVertices(float* vertices);
				std::vector<std::unique_ptr<Shader>>::const_iterator addShader(std::string sourceVertex, std::string sourceFragment);
				std::vector<float*>::const_iterator addColor(float* color);
			// creating vertexattribarrays
				void useColor(std::vector<float*>::const_iterator color);
				void useVertices(std::vector<float*>::const_iterator vertices);
			// draw vertices
				void drawVertices(std::vector<float*>::const_iterator vertices);
			// cleaning
				void disableVertexAttribArrays();
};