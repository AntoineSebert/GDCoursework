#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <memory>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>

#include "Painter.hpp"
#include "EventHandler.hpp"

typedef std::pair<double, double> point;
typedef std::vector<pair<double, double>> points;

std::unique_ptr<Painter> myPainter;
std::unique_ptr<EventHandler> myEventHendler;

SDL_Window* window = nullptr;
SDL_GLContext OpenGLContext = nullptr;
SDL_Event events;
GLenum GLEW;
bool mainCondition = false;