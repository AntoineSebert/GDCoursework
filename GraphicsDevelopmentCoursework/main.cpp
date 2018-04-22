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

bool windowCreation(SDL_Window* window) {
	if(window == nullptr) {
		cout << "Error during the window creation : " << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}
	return true;
}

bool contextCreation(SDL_GLContext OpenGLContext, SDL_Window* window) {
	if(OpenGLContext == nullptr) {
		cout << "Error during the context creation : " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	return true;
}

bool GLEWInitialization(GLenum initialisationGLEW, SDL_GLContext OpenGLContext, SDL_Window* window) {
	if(initialisationGLEW != GLEW_OK) {
		cout << "Error during the initialization of GLEW : " << glewGetErrorString(initialisationGLEW) << endl;
		SDL_GL_DeleteContext(OpenGLContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	return true;
}

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	if(!SDLInitialization())
		return -1;

	setOpenGLAttributes();

	SDL_Window* window = SDL_CreateWindow("Anthony Sébert 1705851", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!windowCreation(window))
		return -1;

	SDL_GLContext OpenGLContext = SDL_GL_CreateContext(window);
	if(!contextCreation(OpenGLContext, window))
		return -1;

	GLenum initialisationGLEW(glewInit());
	if(!GLEWInitialization(initialisationGLEW, OpenGLContext, window))
		return -1;

	float vertices[] = {
		-0.5,
		-0.5,
		 0.0,
		 0.5,
		 0.5,
		-0.5
	};
	SDL_Event events;
	bool terminate(false);

	while(!terminate) {
		SDL_WaitEvent(&events);
		if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			terminate = true;
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		SDL_GL_SwapWindow(window);
	}

	getchar();

	SDL_GL_DeleteContext(OpenGLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}