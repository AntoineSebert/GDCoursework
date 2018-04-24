#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Painter.hpp"
#include "Shader.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

class Scene {
	/* ATTRIBUTES */
		private:
			SDL_Window* window;
			SDL_GLContext openGLContext;
			SDL_Event events;
			GLenum glew;
			bool mainCondition;
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
			bool windowCreation(std::string name, unsigned int height, unsigned int width);
			bool contextCreation();
			bool glewInitialization();
};

