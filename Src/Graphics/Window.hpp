#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class Window sealed
	{
		friend class GraphicsFactory;
	public:
		KALEID_GRAPHICS_API void MakeCurrent();
		KALEID_GRAPHICS_API void SwapBuffers();

		KALEID_GRAPHICS_API void GetSize(unsigned int* width, unsigned int* height);
		KALEID_GRAPHICS_API void SetSize(const unsigned int width, const unsigned int height);

		KALEID_GRAPHICS_API void SetTitle(const char* title);
		KALEID_GRAPHICS_API bool Exists();
		KALEID_GRAPHICS_API static void PollEvents();

	private:
		Window(int width, int height, const char* title);
		void Dispose();
#ifdef KALEID_GRAPHICS_DLL
		GLFWwindow* _handle;
#endif
	};
}
API_END