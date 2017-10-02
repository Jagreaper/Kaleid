#pragma once

#ifdef _WIN32
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
		#define GLFW_DLL
		#include <GLFW/glfw3.h>

		#define KALEID_INPUT_API __declspec(dllexport)
	#else
		#define KALEID_INPUT_API __declspec(dllimport)
	#endif
#endif

#ifdef __cplusplus
	#define API_BEGIN extern "C" {
	#define API_END }
#else
	#define API_BEGIN
	#define API_END
#endif

#include <iostream>