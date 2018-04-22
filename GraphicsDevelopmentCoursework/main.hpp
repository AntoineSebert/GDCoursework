#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <memory>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <list>

#include "Painter.hpp"
#include "EventHandler.hpp"

typedef std::pair<double, double> point;
typedef std::list<pair<double, double>> points;

SDL_Window* window = nullptr;
SDL_GLContext OpenGLContext = nullptr;
SDL_Event events;
GLenum GLEW;
bool mainCondition = false;