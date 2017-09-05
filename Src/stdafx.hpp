#pragma once

#ifdef KALEID_GRAPHICS_DLL
#define KALEID_GRAPHICS_API __declspec(dllexport)
#else
#define KALEID_GRAPHICS_API __declspec(dllimport)
#endif

#ifdef KALEID_GRAPHICS_OPENGL_DLL

#include <GLEW/glew.h> // include GLEW and new version of GL on Windows
#define GLFW_DLL
#include <GLFW/glfw3.h> // GLFW helper library

#define KALEID_GRAPHICS_OPENGL_API __declspec(dllexport)
#else
#define KALEID_GRAPHICS_OPENGL_API __declspec(dllimport)
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

#include <iostream>
#include <GLM/glm.hpp>