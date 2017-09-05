#pragma once

#include "stdafx.hpp"
#include "Window.hpp"

namespace Kaleid::Graphics::OpenGL
{
	class WindowGL sealed : public Window
	{
	public:
		void Dispose();

		void MakeCurrent();
		void SwapBuffers();

		void GetSize(unsigned int* width, unsigned int* height);
		void SetSize(const unsigned int width, const unsigned int height);

		const char* GetTitle();
		void SetTitle(const char* title);
	};
}