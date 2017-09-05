#ifdef KALEID_GRAPHICS_DLL
#define KALEID_GRAPHICS_API __declspec(dllexport);
#else
#define KALEID_GRAPHICS_API __declspec(dllimport);
#endif
