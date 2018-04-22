#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

class Shader {
	/* ATTRIBUTES */
		private:
			GLuint vertexID, fragmentID, programID;
			std::string vertexSource, fragmentSource;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					Shader();
					Shader(std::string sourceVertex, std::string sourceFragment);
				// copy constructor
					Shader(const Shader& other);
				// move constructor
					Shader(Shader&& other) noexcept;
			// destructor
				~Shader() noexcept;
			// operators
				// copy assignment operator
					Shader& operator=(const Shader& other);
				// move assignment operator
					Shader& operator=(Shader&& other) noexcept;
			bool load();
			bool compileShader(GLuint &shader, GLenum type, const std::string& sourceFile);
			GLuint getProgramID() const;
};