#include "SDLWindow.hpp"

using namespace std;

// public
	SDLWindow::SDLWindow() : painter(Painter()) {}
	SDLWindow::SDLWindow(const SDLWindow& other) {}
	SDLWindow::SDLWindow(SDLWindow&& other) noexcept {}
	SDLWindow::~SDLWindow() {}
	SDLWindow& SDLWindow::operator=(const SDLWindow& other) {
		SDLWindow tmp(other);	// re-use copy-constructor  
		*this = move(tmp);		// re-use move-assignment  
		return *this;
	}
	SDLWindow& SDLWindow::operator=(SDLWindow&& other) noexcept {
		if(this == &other)
			return *this;
		return *this;
	}
// protected
	bool SDLWindow::init(SDL_Window* window/*, SDL_GLContext OpenGLContext, GLenum GLEW*/) {
		ready = false;
		if(!SDLInitialization())
			return false;
		setOpenGLAttributes();
		/*
		window = SDL_CreateWindow(
			"Anthony Sébert 1705851",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1000,
			600,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);
		*/
		/*
		if(!windowCreation(window))
			return false;
		OpenGLContext = SDL_GL_CreateContext(window);
		if(!contextCreation(window, OpenGLContext))
			return false;
		GLEW = glewInit();
		if(!GLEWInitialization(window, OpenGLContext, GLEW))
			return false;
		*/
		ready = true;
		return ready;
	}
	/*
	SDL_Window * SDLWindow::getUnderlyingWindow() {
		if(checkIfReady())
			return window;
		return nullptr;
	}
	SDL_GLContext SDLWindow::getContext() {
		if(checkIfReady())
			return OpenGLContext;
		return nullptr;
	}
	*/
	bool SDLWindow::SDLInitialization() {
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "Error during the initialization of the SDL : " << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		return true;
	}
	void SDLWindow::setOpenGLAttributes() {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	}
	bool SDLWindow::windowCreation(SDL_Window* window) {
		if(window == NULL) {
			cout << "Error during the window creation : " << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		return true;
	}
	bool SDLWindow::contextCreation(SDL_Window* window, SDL_GLContext OpenGLContext) {
		if(OpenGLContext == nullptr) {
			cout << "Error during the context creation : " << SDL_GetError() << endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		return true;
	}
	bool SDLWindow::GLEWInitialization(SDL_Window* window, SDL_GLContext OpenGLContext, GLenum GLEW) {
		if(GLEW != GLEW_OK) {
			cout << "Error during the initialization of GLEW : " << glewGetErrorString(GLEW) << endl;
			SDL_GL_DeleteContext(OpenGLContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		return true;
	}
	bool SDLWindow::checkIfReady() {
		if(ready)
			return true;
		cout << "Error : the SDLWindow wrapper has not been initialized" << endl;
		return false;
	}
