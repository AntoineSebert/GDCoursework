#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "utility.h"

class Shader {
	/* ATTRIBUTES */
		private:
			GLuint vertexID, fragmentID, programID;
			std::string vertexSource, fragmentSource;
			static const std::string shadersPath;
	/* MEMBERS */
		public:
			// constructors
				Shader(std::string sourceVertex, std::string sourceFragment);
				Shader(const Shader& other);
				Shader(Shader&& other) noexcept;
			// destructor
				~Shader() noexcept;
			// operators
				inline Shader& operator=(const Shader& other);
				Shader& operator=(Shader&& other) noexcept;
			// other
				bool load();
				GLuint getProgramID() const;
		protected:
			bool compileShader(GLuint &shader, GLenum type, const std::string& sourceFile);
			void displayError();
			void cleanShader();
			bool checkLinking();
			bool checkCompilation(GLuint& shader);
};