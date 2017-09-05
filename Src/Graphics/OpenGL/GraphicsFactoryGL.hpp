#pragma once

#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Graphics::OpenGL
{
	class GraphicsFactoryGL : public GraphicsFactory
	{
	public:
		Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);
	private:
	};
}