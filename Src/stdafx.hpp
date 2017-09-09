#pragma once

#ifdef KALEID_GRAPHICS_DLL

#include <GLEW/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#define KALEID_GRAPHICS_API __declspec(dllexport)
#else
#define KALEID_GRAPHICS_API __declspec(dllimport)
#endif

#ifdef KALEID_GAME_DLL
#define KALEID_GAME_API __declspec(dllexport)
#else
#define KALEID_GAME_API __declspec(dllimport)
#endif

#ifdef KALEID_MATH_DLL
#define KALEID_MATH_API __declspec(dllexport)
#else
#define KALEID_MATH_API __declspec(dllimport)
#endif

#ifdef KALEID_HELPERS_DLL
#define KALEID_HELPERS_API __declspec(dllexport)
#else
#define KALEID_HELPERS_API __declspec(dllimport)
#endif

#include <iostream>
#include <GLM/glm.hpp>