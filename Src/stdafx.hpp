#ifdef KALEID_GRAPHICS_DLL
#define KALEID_GRAPHICS_API __declspec(dllexport);
#else
#define KALEID_GRAPHICS_API __declspec(dllimport);
#endif

#ifdef KALEID_GRAPHICS_OPENGL_DLL
#define KALEID_GRAPHICS_OPENGL_API __declspec(dllexport);
#else
#define KALEID_GRAPHICS_OPENGL_API __declspec(dllimport);
#endif