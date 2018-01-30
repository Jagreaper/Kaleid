#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
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

	#ifdef JAGERTS_KALEID_PHYSICS_DLL
		#define JAGERTS_KALEID_PHYSICS_API __declspec(dllexport)
	#else
		#define JAGERTS_KALEID_PHYSICS_API __declspec(dllimport)
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
#else
	#define JAGERTS_KALEID_GRAPHICS_API
	#define JAGERTS_KALEID_GAME_API
	#define JAGERTS_KALEID_MATH_API 
	#define JAGERTS_KALEID_IO_API
	#define JAGERTS_KALEID_GEOMETRY_API
	#define JAGERTS_KALEID_PHYSICS_API
	#define JAGERTS_KALEID_INPUT_API
#endif

#define jkSetterBody(_VALUE) _VALUE = value

#define jkSetterHeader(_NAME, _TYPE) void Set ## _NAME(_TYPE value)

#define jkSetterHeaderDefinition(_NAME, _TYPE, _VALUE) jkSetterHeader(_NAME, _TYPE) { jkSetterBody(_VALUE); }

#define jkSetterSource(_CLASS, _NAME, _TYPE) void _CLASS::Set ## _NAME(_TYPE value)

#define jkSetterSourceDefinition(_CLASS, _NAME, _TYPE, _VALUE) jkSetterSource(_CLASS, _NAME, _TYPE) { jkSetterBody(_VALUE);}

#define jkGetterBody(_VALUE) return _VALUE

#define jkGetterHeader(_NAME, _TYPE) _TYPE Get ## _NAME() const

#define jkGetterHeaderDefinition(_NAME, _TYPE, _VALUE) jkGetterHeader(_NAME, _TYPE) { jkGetterBody(_VALUE); }

#define jkGetterSource(_CLASS, _NAME, _TYPE) _TYPE _CLASS::Get ## _NAME() const

#define jkGetterSourceDefinition(_CLASS, _NAME, _TYPE, _VALUE) jkGetterSource(_CLASS, _NAME, _TYPE) { jkGetterBody(_VALUE); }

#define jkGetterSetterHeader(_NAME, _TYPE) \
jkSetterHeader(_NAME, _TYPE); \
jkGetterHeader(_NAME, _TYPE&) \

#define jkGetterSetterHeaderDefinition(_NAME, _TYPE, _VALUE) \
jkSetterHeaderDefinition(_NAME, _TYPE, _VALUE) \
jkGetterHeaderDefinition(_NAME, _TYPE&, _VALUE) \

#define jkGetterSetterSourceDefinition(_CLASS, _NAME, _TYPE, _VALUE) \
jkSetterSourceDefinition(_CLASS, _NAME, _TYPE, _VALUE) \
jkGetterSourceDefinition(_CLASS, _NAME, _TYPE&, _VALUE) \

