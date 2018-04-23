#include "main.hpp"

using namespace std;

void setOpenGLAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

bool SDLInitialization() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Error during the initialization of the SDL : " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}
	return true;
}

bool windowCreation() {
	if(window == nullptr) {
		cout << "Error during the window creation : " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}
	return true;
}

bool contextCreation() {
	if(OpenGLContext == nullptr) {
		cout << "Error during the context creation : " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	return true;
}

bool GLEWInitialization() {
	if(GLEW != GLEW_OK) {
		cout << "Error during the initialization of GLEW : " << glewGetErrorString(GLEW) << endl;
		SDL_GL_DeleteContext(OpenGLContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	return true;
}

bool init() {
	if(!SDLInitialization())
		return false;
	setOpenGLAttributes();
	window = SDL_CreateWindow("Anthony Sébert 1705851", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!windowCreation())
		return false;
	OpenGLContext = SDL_GL_CreateContext(window);
	if(!contextCreation())
		return false;
	GLEW = glewInit();
	if(!GLEWInitialization())
		return false;
	return true;
}

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	init();

	float vertices[] = {
		-0.5,
		-0.5,
		 0.0,
		 0.5,
		 0.5,
		-0.5
	};

	Shader shaderBasique("Shaders/basic2D.vert", "Shaders/basic2D.frag");
	shaderBasique.load();

	while(!mainCondition) {
		SDL_WaitEvent(&events);
		if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			mainCondition = true;
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderBasique.getProgramID());
		myPainter.drawTriangles(vertices);
		glUseProgram(0);
		SDL_GL_SwapWindow(window);
	}

	getchar();

	SDL_GL_DeleteContext(OpenGLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}