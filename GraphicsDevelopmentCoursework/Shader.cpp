#include "Shader.h"

using namespace std;

// public
	Shader::Shader(string vertexSource, string fragmentSource)
		: vertexID(0), fragmentID(0), programID(0), vertexSource(vertexSource), fragmentSource(fragmentSource) {}
	Shader::Shader(const Shader& other)
		: vertexID(other.vertexID), fragmentID(other.fragmentID), programID(other.programID), vertexSource(other.vertexSource), fragmentSource(other.fragmentSource) {}
	Shader::Shader(Shader&& other) noexcept
		: vertexID(other.vertexID), fragmentID(other.fragmentID), programID(other.programID), vertexSource(other.vertexSource), fragmentSource(other.fragmentSource) {
		glDeleteShader(other.vertexID);
		glDeleteShader(other.fragmentID);
		glDeleteProgram(other.programID);
	}
	Shader::~Shader() {
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		glDeleteProgram(programID);
	}
	Shader& Shader::operator=(const Shader& other) { return (*this = move(Shader(other))); }
	Shader& Shader::operator=(Shader&& other) noexcept {
		if(this == &other)
			return *this;

		vertexID = other.vertexID;
		fragmentID = other.fragmentID;
		programID = other.programID;
		vertexSource = other.vertexSource;
		fragmentSource = other.fragmentSource;
		glDeleteShader(other.vertexID);
		glDeleteShader(other.fragmentID);
		glDeleteProgram(other.programID);

		return *this;
	}
	bool Shader::load() {
		// check vertices and fragments compilation
		if(cleanShader(); !compileShader(vertexID, GL_VERTEX_SHADER, vertexSource) || !compileShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
			return false;
		// creation of the program
		programID = glCreateProgram();
		// combining the shaders
		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		// locking the shader inputs
		glBindAttribLocation(programID, 0, "in_Vertex");
		glBindAttribLocation(programID, 1, "in_Color");
		glBindAttribLocation(programID, 2, "in_TexCoord0");
		// program linking
		glLinkProgram(programID);

		return checkLinking();
	}
	GLuint Shader::getProgramID() const { return programID; }
// protected
	bool Shader::compileShader(GLuint& shader, GLenum type, const string& sourceFile) {
		// shader creation
		if(shader = glCreateShader(type); shader == 0) {
			cout << "Error : the type of shader (" << type << ") does not exist" << endl;
			return false;
		}
		auto file_content = extractFileContent(sourceFile);
		if(!file_content)
			return false;
		if(file_content->empty()) {
			glDeleteShader(shader);
			return false;
		}
		const GLchar* chaineCodeSource = file_content->c_str();
		// Sending the source code to the shader
		glShaderSource(shader, 1, &chaineCodeSource, 0);
		// compiling the shader
		glCompileShader(shader);
		// checking the shader
		return checkCompilation(shader);
	}
	void Shader::displayError() {
		// get the error size
		GLint errorSize(0);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorSize);
		// memory allocation
		char *error = new char[errorSize + 1];
		// get the error
		glGetShaderInfoLog(programID, errorSize, &errorSize, error);
		error[errorSize] = '\0';
		// displaying the error
		cout << error << endl;
		delete[] error;
	}
	void Shader::cleanShader() {
		// destruction of a potential old shader
		if(glIsShader(vertexID) == GL_TRUE)
			glDeleteShader(vertexID);
		if(glIsShader(fragmentID) == GL_TRUE)
			glDeleteShader(fragmentID);
		if(glIsProgram(programID) == GL_TRUE)
			glDeleteProgram(programID);
	}
	bool Shader::checkLinking() {
		// checking the linking
		GLint linkError(0);
		if(glGetProgramiv(programID, GL_LINK_STATUS, &linkError); linkError != GL_TRUE) {
			displayError();
			glDeleteProgram(programID);
			return false;
		}
		return true;
	}
	bool Shader::checkCompilation(GLuint& shader) {
		// compile and check
		GLint compilationError(0);
		if(glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError); compilationError != GL_TRUE) {
			displayError();
			glDeleteShader(shader);
			return false;
		}
		return true;
	}