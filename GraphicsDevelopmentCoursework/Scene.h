#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric> // std:accumulate
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#pragma warning(push, 0) // disable warnings
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#pragma warning(pop)

#include "Object.h"
#include "utility.h"
#include "Viewport.h"

class Scene {
	/* ATTRIBUTES */
		private:
			SDL_Window* window;
			SDL_GLContext openGLContext;
			SDL_Event events;
			GLenum glew;
			bool mainCondition;
			std::map<std::string, Object> objects;
			std::map<std::string, std::vector<float>> colors;
			std::map<std::string, Shader> shaders;
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
				inline Scene& operator=(const Scene& other);
				Scene& operator=(Scene&& other) noexcept;
			// program loop
				bool mainLoop();
		protected:
			// initializations
				bool SDLInitialization();
				inline void setOpenGLAttributes();
				bool windowCreation(std::string name, unsigned int width, unsigned int height);
				bool contextCreation();
				bool glewInitialization();
			// set up colors and objects
				void createPalette();
				void createObjects();
				inline void createAndLoadshaders();
			// other
				bool import3DSMaxFile(std::string filename, std::vector<float>& output);
				void eventsHandler();
				void displayobjects(std::list<std::pair<Object, std::optional<std::list<glm::mat4>>>> objects_to_display);
};