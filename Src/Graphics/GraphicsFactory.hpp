#pragma once

#include "stdafx.hpp"
#include "Window.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API GraphicsFactory
	{
	public:
		Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);
	private:
	};
}