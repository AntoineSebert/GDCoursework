#pragma once

#include <array>
#include <filesystem>
#include <iostream>
#include <stdio.h>

#pragma warning(push, 0) // disable warnings
#include <SDL.h>
#include <GL/glew.h>
#pragma warning(pop)

#include "Scene.h"

std::unique_ptr<Scene> myScene;