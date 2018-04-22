#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <list>
#include <memory>
#include <utility>
#include <vector>

typedef std::pair<float, float> point;
typedef std::list<std::pair<float, float>> points;

class Painter {
	/* ATTRIBUTES */
		private:
			std::shared_ptr<std::vector<points>> data;
			static std::vector<std::shared_ptr<std::vector<points>>> globalData;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					Painter();
				// copy constructor
					Painter(const Painter& other) : data(other.getDataPointer()) {}
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
				std::shared_ptr<std::vector<points>> getDataPointer() const;
			// drawing
				void drawTriangles(float* vertices);
};