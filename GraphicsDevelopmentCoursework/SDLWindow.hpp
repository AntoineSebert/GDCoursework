#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <algorithm>
#include <iostream>

#include "Painter.hpp"

class SDLWindow {
	/* ATTRIBUTES */
		private:
			bool ready;
		public:
			Painter painter;
	/* MEMBERS */
		public:
			// constructors
				// default constructor
					SDLWindow();
				// copy constructor
					SDLWindow(const SDLWindow& other);
				// move constructor
					SDLWindow(SDLWindow&& other) noexcept;
			// destructor
				~SDLWindow() noexcept;
			// operators
				// copy assignment operator
					SDLWindow& operator=(const SDLWindow& other);
				// move assignment operator
					SDLWindow& operator=(SDLWindow&& other) noexcept;
			// initialization
				bool init(SDL_Window* window/*, SDL_GLContext OpenGLContext, GLenum GLEW*/);
			// getters
				/*
				SDL_Window* getUnderlyingWindow();
				SDL_GLContext getContext();
				*/
		//protected:
			bool SDLInitialization();
			void setOpenGLAttributes();
			bool windowCreation(SDL_Window* window);
			bool contextCreation(SDL_Window* window, SDL_GLContext OpenGLContext);
			bool GLEWInitialization(SDL_Window* window, SDL_GLContext OpenGLContext, GLenum GLEW);
			bool checkIfReady();
};

