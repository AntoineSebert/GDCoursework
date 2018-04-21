#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
		SDL_Quit();
		return -1;
	}

	// Version d'OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	// Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_Window* fenetre(0);
	fenetre = SDL_CreateWindow("Phusis krupthestai philei", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(fenetre == 0) {
		cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
		SDL_Quit();
		return -1;
	}

	SDL_GLContext contexteOpenGL(0);
	contexteOpenGL = SDL_GL_CreateContext(fenetre);
	if (contexteOpenGL == 0) {
		cout << SDL_GetError() << endl;
		SDL_DestroyWindow(fenetre);
		SDL_Quit();
		return -1;
	}

	SDL_Event evenements;
	bool terminer(false);
	while(!terminer) {
		SDL_WaitEvent(&evenements);
		if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = true;
	}

	getchar();

	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();

	return 0;
}