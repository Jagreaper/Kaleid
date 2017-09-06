#pragma once

#include "stdafx.hpp"
#include "Window.hpp"
#include "ShaderProgram.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API GraphicsFactory
	{
	public:
		Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);
		ShaderProgram* CreateShaderProgram(const char** sources, const ShaderType* types, const unsigned short count);
	private:
	};
}