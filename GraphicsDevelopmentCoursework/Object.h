#pragma once

#include <vector>

class Object {
	/* ATTRIBUTES */
		private:
			std::vector<float> vertices;
			std::vector<float> colors;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					Object(std::vector<float>* newVertices, std::vector<float>* newColors);
				// copy constructor
					Object(const Object& other);
				// move constructor
					Object(Object&& other) noexcept;
			// destructor
				~Object() noexcept;
			// operators
				// copy assignment operator
					Object& operator=(const Object& other);
				// move assignment operator
					Object& operator=(Object&& other) noexcept;
			// getters
				// thou shalt not modify these objects
				const std::vector<float>& getVertices() const;
				const std::vector<float>& getColors() const;
};

