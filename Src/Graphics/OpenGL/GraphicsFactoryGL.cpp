#include "stdafx.hpp"
#include "GraphicsFactoryGL.hpp"
#include "WindowGL.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Graphics::OpenGL;

Window* GraphicsFactoryGL::CreateWindow(const unsigned int width, const unsigned int height, const char* title)
{
	Window* window = new WindowGL();
	window->SetTitle(title);
	window->SetSize(width, height);
	return window;
}