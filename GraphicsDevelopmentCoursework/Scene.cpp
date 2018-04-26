#include "Scene.hpp"

using namespace std;
using namespace glm;

// public
	Scene::Scene(string name, unsigned int height, unsigned int width)
		: window(nullptr), openGLContext(nullptr), glew(0), mainCondition(false), height(height), width(width) {
		if(SDLInitialization() && windowCreation(name, height, width) && contextCreation() && glewInitialization()) {
			mainCondition = true;
			myPainter = unique_ptr<Painter>(new Painter());
		}
	}
	Scene::Scene(const Scene& other)
		: window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew), mainCondition(other.mainCondition), height(height), width(width) {}
	Scene::Scene(Scene&& other) noexcept
		: window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew), mainCondition(other.mainCondition), height(height), width(width) {
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
		this->height = height;
		this->width = width;
		return *this;
	}
	bool Scene::mainLoop() {
		// matrix
			mat4 projection = perspective(70.0, (double)width / height, 1.0, 100.0), modelview = mat4(1.0);
		// colors
			auto blue = myPainter->addColor(vector<float>({
				0.0, (float)(204.0 / 255.0), 1.0,
				0.0, (float)(204.0 / 255.0), 1.0,
				0.0, (float)(204.0 / 255.0), 1.0
			})),
			multicolor = myPainter->addColor(vector<float>({
				1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 0.0, 1.0
			}))/*,
			red = myPainter->addColor(array<float, 18>({
				-1.0, -1.0, -1.0,	1.0, -1.0, -1.0,	1.0, 1.0, -1.0,
				-1.0, -1.0, -1.0,	-1.0, 1.0, -1.0,	1.0, 1.0, -1.0
			}).data())*/;
		// 3D objects
			auto triangle = myPainter->addVertices(vector<float>({ 0.5, 0.5, 0.0, -0.5, -0.5, 0.5 })),
			square = myPainter->addVertices(vector<float>({
				-1.0, -1.0, -1.0,	1.0, -1.0, -1.0,	1.0, 1.0, -1.0,
				-1.0, -1.0, -1.0,	-1.0, 1.0, -1.0,	1.0, 1.0, -1.0
			}));
		// shader
			auto shader = myPainter->addShader("color3D.vert", "color3D.frag");

		if(shader != myPainter->shadersEnd()) {
			while(mainCondition) {
				SDL_WaitEvent(&events);
				if(events.window.event == SDL_WINDOWEVENT_CLOSE)
					mainCondition = false;
				glClear(GL_COLOR_BUFFER_BIT);
				modelview = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
				glUseProgram(shader->get()->getProgramID()); // send shader to graphic card
				{
					myPainter->useColor(multicolor);	// send color to shader
					myPainter->useVertices(square);	// send vertices to shader
					glUniformMatrix4fv(
						glGetUniformLocation(shader->get()->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection)
					);
					glUniformMatrix4fv(
						glGetUniformLocation(shader->get()->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview)
					);

					myPainter->drawVertices(square);
					myPainter->disableVertexAttribArrays();

				}
				glUseProgram(0);
				SDL_GL_SwapWindow(window);
			}
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
	bool Scene::windowCreation(string name, unsigned int newHeight, unsigned int newWidth) {
		setOpenGLAttributes();
		window = SDL_CreateWindow(
			name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			height,
			width,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);
		if(window == nullptr) {
			cout << "Error during the window creation : " << SDL_GetError() << endl;
			SDL_Quit();
			return false;
		}
		height = newHeight;
		width = newWidth;
		return true;
	}
	bool Scene::contextCreation() {
		openGLContext = SDL_GL_CreateContext(window);
		if(openGLContext == nullptr) {
			cout << "Error during the context creation : " << SDL_GetError() << endl;
			SDL_DestroyWindow(window);
			return false;
		}
		return true;
	}
	bool Scene::glewInitialization() {
		glew = glewInit();
		if(glew != GLEW_OK) {
			cout << "Error during the initialization of GLEW : " << glewGetErrorString(glew) << endl;
			SDL_GL_DeleteContext(openGLContext);
			SDL_DestroyWindow(window);
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