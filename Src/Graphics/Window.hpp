#pragma once

#include "stdafx.hpp"

namespace Kaleid::Graphics
{
	class Window
	{
	public:
		void Dispose();

		KALEID_GRAPHICS_API void MakeCurrent();
		KALEID_GRAPHICS_API void SwapBuffers();

		KALEID_GRAPHICS_API void GetSize(unsigned int* width, unsigned int* height);
		KALEID_GRAPHICS_API void SetSize(const unsigned int width, const unsigned int height);

		KALEID_GRAPHICS_API const char* GetTitle();
		KALEID_GRAPHICS_API void SetTitle(const char* title);
	};
}