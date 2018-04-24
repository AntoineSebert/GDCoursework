#include "main.hpp"

using namespace std;

bool init() {
	//myWindow.init();
	if(!myWindow.SDLInitialization())
		return false;
	myWindow.setOpenGLAttributes();
	window = SDL_CreateWindow("Anthony Sébert 1705851", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!myWindow.windowCreation(window))
		return false;
	OpenGLContext = SDL_GL_CreateContext(window);
	if(!myWindow.contextCreation(window, OpenGLContext))
		return false;
	GLEW = glewInit();
	if(!myWindow.GLEWInitialization(window, OpenGLContext, GLEW))
		return false;
	return true;
}

int main(int argc, char* argv[]) {
	for(unsigned int i = 0; i < (unsigned int)argc; i++)
		printf("Argument %ld : %s \n", i + 1, argv[i]);

	myWindow = SDLWindow();
	if(init()) {

		Shader shaderBasique("Shaders/basic2D.vert", "Shaders/basic2D.frag");
		shaderBasique.load();

		while(!mainCondition) {
			SDL_WaitEvent(&events);
			if(events.window.event == SDL_WINDOWEVENT_CLOSE)
				mainCondition = true;
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderBasique.getProgramID());
			myWindow.painter.drawTriangles(array<float, 6>({ 0.5, 0.5, 0.0, -0.5, -0.5, 0.5 }).data());
			glUseProgram(0);
			SDL_GL_SwapWindow(window);
		}

		getchar();

		SDL_GL_DeleteContext(OpenGLContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	return 0;
}