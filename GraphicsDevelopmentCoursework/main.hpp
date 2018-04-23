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
#include "Shader.h"

typedef std::pair<float, float> point;
typedef std::list<std::pair<float, float>> points;

SDL_Window* window = nullptr;
SDL_GLContext OpenGLContext = nullptr;
SDL_Event events;
GLenum GLEW;
bool mainCondition = false;

Painter myPainter = Painter();