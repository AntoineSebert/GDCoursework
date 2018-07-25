#pragma once

#pragma warning(push, 0) // disable warnings
#include <SDL.h>
#include <GL/glew.h>
#pragma warning(pop)

#include <array>
#include <filesystem>
#include <iostream>
#include <stdio.h>

#include "Scene.hpp"

std::unique_ptr<Scene> myScene;