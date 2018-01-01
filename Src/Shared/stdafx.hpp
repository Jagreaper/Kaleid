#pragma once

#ifdef KALEID_GRAPHICS_DLL
	#define KALEID_INPUT_HEADERS

	#include <GLEW/glew.h>

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

#ifdef KALEID_IO_DLL
	#define KALEID_IO_API __declspec(dllexport)
#else
	#define KALEID_IO_API __declspec(dllimport)
#endif

#ifdef KALEID_GEOMETRY_DLL
	#define KALEID_GEOMETRY_API __declspec(dllexport)
#else
	#define KALEID_GEOMETRY_API __declspec(dllimport)
#endif

#ifdef KALEID_IMAGING_DLL
	#define KALEID_IMAGING_API __declspec(dllexport)
#else
	#define KALEID_IMAGING_API __declspec(dllimport)
#endif

#ifdef KALEID_INPUT_DLL
	#define KALEID_INPUT_HEADERS

	#define KALEID_INPUT_API __declspec(dllexport)
#else
	#define KALEID_INPUT_API __declspec(dllimport)
#endif

#ifdef KALEID_XML_DLL
	#define KALEID_XML_API __declspec(dllexport)
#else
	#define KALEID_XML_API __declspec(dllimport)
#endif

#ifdef KALEID_INPUT_HEADERS
	#define GLFW_DLL
	#include <GLFW/glfw3.h>
#endif