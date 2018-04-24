#include "main.hpp"

using namespace std;

bool init() {
	/*
	if(!myWindow.init(window))
		return false;
	window = SDL_CreateWindow(
		"Anthony Sébert 1705851",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000,
		600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);
	if(!myWindow.windowCreation(window))
		return false;
	OpenGLContext = SDL_GL_CreateContext(window);
	if(!myWindow.contextCreation(window, OpenGLContext))
		return false;
	GLEW = glewInit();
	if(!myWindow.GLEWInitialization(window, OpenGLContext, GLEW))
		return false;
	*/
	return true;
}

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	(myScene = unique_ptr<Scene>(new Scene("Anthony Sébert 1705851", 1000, 600)))->mainLoop();

	SDL_Quit();
	getchar();

	return 0;
}