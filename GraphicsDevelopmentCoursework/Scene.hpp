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
#include "Painter.hpp"
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
			std::unique_ptr<Painter> myPainter;
			unsigned int height, width;
			std::map<std::string, Object> availableObjects;
			std::array<Viewport, 2> viewports;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
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
			// initializations
				void initLeftViewport(glm::mat4& matrix);
				void initRightViewport(glm::mat4& matrix);
				bool SDLInitialization();
				void setOpenGLAttributes();
				bool windowCreation(std::string name);
				bool contextCreation();
				bool glewInitialization();
			// set up colors and objects
				void createPalette();
				void createObjects();
			// other
				bool import3DSMaxFile(std::string filename, std::vector<float>& output);
				void eventsHandler();
				void resize();
				void gluPerspective(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};