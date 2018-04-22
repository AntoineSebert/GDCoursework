#pragma once

#include <list>
#include <memory>
#include <utility>
#include <vector>

typedef std::pair<double, double> point;
typedef std::list<std::pair<double, double>> points;

class Painter {
	/* ATTRIBUTES */
		private:
			std::shared_ptr<std::vector<points>> data;
			static std::vector<std::shared_ptr<std::vector<points>>> globalData;
	/* MEMBERS */
		public:
			// constructors
				// Default constructor
					Painter();
				// Copy constructor
					Painter(const Painter& other) : data(other.getDataPointer()) {}
				// Move constructor
					Painter(Painter&& other) noexcept;
			// Destructor
					~Painter() noexcept;
			// Operators
				// Copy assignment operator
					Painter& operator=(const Painter& other);
				// Move assignment operator
					Painter& operator=(Painter&& other) noexcept;
			// Getters
				std::shared_ptr<std::vector<points>> getDataPointer() const;
		protected:
			bool draw2D(points myPoints);
			bool draw3D(points myPoints);
};