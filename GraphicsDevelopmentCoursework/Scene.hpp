#pragma once

#pragma warning(push, 0) // disable warnings
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#pragma warning(pop)

#include "Object.h"
#include "utility.hpp"
#include "Viewport.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Scene {
	/* ATTRIBUTES */
		private:
			SDL_Window* window;
			SDL_GLContext openGLContext;
			SDL_Event events;
			GLenum glew;
			bool mainCondition;
			std::map<std::string, Object> availableObjects;
			std::map<std::string, std::vector<float>> availableColors;
			std::map<std::string, Shader> availableShaders;
			std::vector<std::shared_ptr<Viewport>> viewports;
			const unsigned int framerate = 1000 / 50;
	/* MEMBERS */
		public:
			// constructors
				Scene(std::string name, unsigned int height, unsigned int width);
				Scene(const Scene& other);
				Scene(Scene&& other) noexcept;
			// destructor
				~Scene() noexcept;
			// operators
				Scene& operator=(const Scene& other);
				Scene& operator=(Scene&& other) noexcept;
			// program loop
				bool mainLoop();
		protected:
			// initializations
				bool SDLInitialization();
				void setOpenGLAttributes();
				bool windowCreation(std::string name, unsigned int width, unsigned int height);
				bool contextCreation();
				bool glewInitialization();
			// set up colors and objects
				void createPalette();
				void createObjects();
				void createAndLoadShaders();
			// other
				bool import3DSMaxFile(std::string filename, std::vector<float>& output);
				void eventsHandler();
};