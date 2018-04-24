#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <memory>
#include <utility>
#include <vector>

// TODO rule of zero ?

class Painter {
	/* ATTRIBUTES */
		private:
			std::vector<float*> data;
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
			// drawing
				static void drawTriangles(float* vertices);
};