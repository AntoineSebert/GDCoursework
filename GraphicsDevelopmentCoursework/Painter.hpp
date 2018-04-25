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
			std::vector<std::unique_ptr<Shader>> shaders;
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
				std::vector<std::unique_ptr<Shader>>::const_iterator end() const;
			// drawing
				void drawTriangles(float* vertices);
			// shaders
				std::vector<std::unique_ptr<Shader>>::const_iterator addShader(std::string sourceVertex, std::string sourceFragment);
};