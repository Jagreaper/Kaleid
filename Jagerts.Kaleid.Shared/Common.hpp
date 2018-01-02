#pragma once

#ifdef JAGERTS_KALEID_GRAPHICS_DLL
	#define JAGERTS_KALEID_INPUT_HEADERS

	#include <GLEW/glew.h>

	#define JAGERTS_KALEID_GRAPHICS_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_GRAPHICS_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_GAME_DLL
	#define JAGERTS_KALEID_GAME_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_GAME_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_MATH_DLL
	#define JAGERTS_KALEID_MATH_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_MATH_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_IO_DLL
	#define JAGERTS_KALEID_IO_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_IO_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_GEOMETRY_DLL
	#define JAGERTS_KALEID_GEOMETRY_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_GEOMETRY_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_INPUT_DLL
	#define JAGERTS_KALEID_INPUT_HEADERS

	#define JAGERTS_KALEID_INPUT_API __declspec(dllexport)
#else
	#define JAGERTS_KALEID_INPUT_API __declspec(dllimport)
#endif

#ifdef JAGERTS_KALEID_INPUT_HEADERS
	#define GLFW_DLL
	#include <GLFW/glfw3.h>
#endif