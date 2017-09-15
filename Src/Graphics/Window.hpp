#pragma once

#include "stdafx.hpp"

namespace Kaleid::Graphics
{
	class Window
	{
	public:
		KALEID_GRAPHICS_API void MakeCurrent();
		KALEID_GRAPHICS_API void SwapBuffers();

		KALEID_GRAPHICS_API void GetSize(unsigned int* width, unsigned int* height);
		KALEID_GRAPHICS_API void SetSize(const unsigned int width, const unsigned int height);

		KALEID_GRAPHICS_API void SetTitle(const char* title);
		KALEID_GRAPHICS_API bool Exists();
		KALEID_GRAPHICS_API void PollEvents();
#ifdef KALEID_GRAPHICS_DLL
		Window(int width, int height, const char* title);

		void Dispose();
	private:
		GLFWwindow* _handle;
#endif
	};
}