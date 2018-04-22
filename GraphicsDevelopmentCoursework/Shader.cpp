#include "Shader.h"

using namespace std;

Shader::Shader() : vertexID(0), fragmentID(0), programID(0), vertexSource(""), fragmentSource("") {}
Shader::Shader(string vertexSource, string fragmentSource) : vertexID(0), fragmentID(0), programID(0), vertexSource(vertexSource), fragmentSource(fragmentSource) {}
Shader::Shader(const Shader& other) {
	vertexSource = other.vertexSource;
	fragmentSource = other.fragmentSource;
	load();
}
Shader::Shader(Shader&& other) noexcept
	: vertexID(other.vertexID), fragmentID(other.fragmentID), programID(other.programID), vertexSource(other.vertexSource), fragmentSource(other.fragmentSource) {
	glDeleteShader(other.vertexID);
	glDeleteShader(other.fragmentID);
	glDeleteProgram(other.programID);
	load();
}
Shader::~Shader() {
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
}
Shader& Shader::operator=(const Shader& other) {
	vertexSource = other.vertexSource;
	fragmentSource = other.fragmentSource;
	load();
	return *this;
}
Shader & Shader::operator=(Shader && other) noexcept {
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
	// destruction of a potential old shader
	if(glIsShader(vertexID) == GL_TRUE)
		glDeleteShader(vertexID);
	if(glIsShader(fragmentID) == GL_TRUE)
		glDeleteShader(fragmentID);
	if(glIsProgram(programID) == GL_TRUE)
		glDeleteProgram(programID);
	// compiling the shaders
	if(!compileShader(vertexID, GL_VERTEX_SHADER, vertexSource))
		return false;
	if(!compileShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
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
	// checking the linking
	GLint linkError(0);
	glGetProgramiv(programID, GL_LINK_STATUS, &linkError);
	if(linkError != GL_TRUE) {
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
		// Libération de la mémoire et retour du booléen false
		delete[] error;
		glDeleteProgram(programID);
		return false;
	}
	return true;
}
bool Shader::compileShader(GLuint& shader, GLenum type, const string& sourceFile) {
	// shader creation
	shader = glCreateShader(type);
	// checking the shader
	if(shader == 0) {
		cout << "Error : the type of shader (" << type << ") does not exist" << endl;
		return false;
	}
	// reading stream
	ifstream file(sourceFile.c_str());
	// opening test
	if(!file) {
		cout << "Error : the file " << sourceFile << " cannot be found" << endl;
		glDeleteShader(shader);
		return false;
	}
	string line, sourceCode;
	while(getline(file, line))
		sourceCode += line + '\n';
	file.close();
	const GLchar* chaineCodeSource = sourceCode.c_str();
	// Sending the source code to the shader
	glShaderSource(shader, 1, &chaineCodeSource, 0);
	// compiling the shader
	glCompileShader(shader);
	// checking the compilation
	GLint compilationError(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);
	if(compilationError != GL_TRUE) {
		// get the error size
		GLint errorSize(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
		// memory allocation
		char *error = new char[errorSize + 1];
		// get the error
		glGetShaderInfoLog(shader, errorSize, &errorSize, error);
		error[errorSize] = '\0';
		// displaying the error
		cout << error << endl;
		delete[] error;
		glDeleteShader(shader);
		return false;
	}
	return true;
}
GLuint Shader::getProgramID() const { return programID; }