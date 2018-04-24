#include "Scene.hpp"

using namespace std;

// public
	Scene::Scene(string name, unsigned int height, unsigned int width) : window(nullptr), openGLContext(nullptr), glew(0), mainCondition(false) {
		if(SDLInitialization())
			mainCondition = true;
		setOpenGLAttributes();
	}
	Scene::Scene(const Scene& other) : window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew), mainCondition(other.mainCondition) {}
	Scene::Scene(Scene&& other) noexcept : window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew), mainCondition(other.mainCondition) {
		SDL_GL_DeleteContext(other.openGLContext);
		SDL_DestroyWindow(other.window);
	}
	Scene::~Scene() {
		SDL_GL_DeleteContext(openGLContext);
		SDL_DestroyWindow(window);
	}
	Scene& Scene::operator=(const Scene& other) { return (*this = move(Scene(other))); }
	Scene& Scene::operator=(Scene&& other) noexcept {
		if(this == &other)
			return *this;
		SDL_GL_DeleteContext(openGLContext);
		SDL_DestroyWindow(window);
		openGLContext = other.openGLContext;
		window = other.window;
		events = other.events;
		glew = other.glew;
		mainCondition = other.mainCondition;
	}
	bool Scene::mainLoop() {
		Shader shaderBasique("Shaders/basic2D.vert", "Shaders/basic2D.frag");
		shaderBasique.load();

		while(!mainCondition) {
			SDL_WaitEvent(&events);
			if(events.window.event == SDL_WINDOWEVENT_CLOSE)
				mainCondition = true;
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderBasique.getProgramID());
			Painter::drawTriangles(array<float, 6>({ 0.5, 0.5, 0.0, -0.5, -0.5, 0.5 }).data());
			glUseProgram(0);
			SDL_GL_SwapWindow(window);
		}
		return false;
	}
// protected
	bool Scene::SDLInitialization() {
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		return true;
	}
	void Scene::setOpenGLAttributes() {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	}
	bool Scene::windowCreation() {
		return false;
	}
	bool Scene::contextCreation() {
		return false;
	}
	bool Scene::glewInitialization() {
		return false;
	}