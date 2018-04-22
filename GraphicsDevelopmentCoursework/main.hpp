#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <memory>
#include <iostream>
#include <stdio.h>
#include <utility>

#include "Graphics.hpp"

typedef std::pair<double, double> point;

std::unique_ptr<Graphics> myGraphics;

SDL_Window* window = nullptr;
SDL_GLContext OpenGLContext = nullptr;
SDL_Event events;
GLenum GLEW;
bool mainCondition = false;