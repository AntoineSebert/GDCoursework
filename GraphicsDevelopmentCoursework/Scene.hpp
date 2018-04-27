#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "Object.h"
#include "Painter.hpp"
#include "utility.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
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
			std::unique_ptr<Painter> myPainter;
			unsigned int height, width;
			// std::map<std::string, Object> availableObjects;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					Scene() = delete;
					Scene(std::string name, unsigned int height, unsigned int width);
				// copy constructor
					Scene(const Scene& other);
				// move constructor
					Scene(Scene&& other) noexcept;
			// destructor
				~Scene() noexcept;
			// operators
				// copy assignment operator
					Scene& operator=(const Scene& other);
				// move assignment operator
					Scene& operator=(Scene&& other) noexcept;
			// program loop
				bool mainLoop();
		protected:
			bool SDLInitialization();
			void setOpenGLAttributes();
			bool windowCreation(std::string name, unsigned int newHeight, unsigned int newWidth);
			bool contextCreation();
			bool glewInitialization();
			void createPalette();
			std::vector<float> import3DSMaxFile(std::string filename);
};

