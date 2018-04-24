#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <array>
#include <iostream>
#include <stdio.h>

#include "EventHandler.hpp"
#include "SDLWindow.hpp"
#include "Shader.h"

SDL_Window* window = nullptr;
SDL_GLContext OpenGLContext = nullptr;
SDL_Event events;
GLenum GLEW;
bool mainCondition = false;

SDLWindow myWindow;