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

#define jkSetterBody(VALUE) VALUE = value

#define jkSetterHeader(NAME, TYPE) void Set##NAME##(TYPE value)

#define jkSetterHeaderDefinition(NAME, TYPE, VALUE) jkSetterHeader(NAME, TYPE) { jkSetterBody(VALUE); }

#define jkSetterSource(CLASS, NAME, TYPE) void ##CLASS##::Set##NAME##(TYPE value)

#define jkSetterSourceDefinition(CLASS, NAME, TYPE, VALUE) jkSetterSource(CLASS, NAME, TYPE) { jkSetterBody(VALUE);}

#define jkGetterBody(VALUE) return VALUE

#define jkGetterHeader(NAME, TYPE) TYPE Get##NAME##()

#define jkGetterHeaderDefinition(NAME, TYPE, VALUE) jkGetterHeader(NAME, TYPE) { jkGetterBody(VALUE); }

#define jkGetterSource(CLASS, NAME, TYPE) TYPE ##CLASS##::Get##NAME##()

#define jkGetterSourceDefinition(CLASS, NAME, TYPE, VALUE) jkGetterSource(CLASS, NAME, TYPE) { jkGetterBody(VALUE); }

#define jkGetterSetterHeaderDefinition(NAME, TYPE, VALUE) \
jkSetterHeaderDefinition(NAME, const TYPE, VALUE); \
jkSetterHeaderDefinition(NAME, const TYPE&, VALUE); \
jkGetterHeaderDefinition(NAME, const TYPE&, VALUE) \

