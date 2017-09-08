#pragma once

#include "stdafx.hpp"
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API GraphicsFactory
	{
	public:
		Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);
		Shader* CreateShader(const char** source, const ShaderType type);
		Shader** CreateShaders(const char*** sources, const ShaderType* types, const unsigned short count);
		Shader** CreateShaders(const std::vector<const char**>& sources, const std::vector<ShaderType>& types);
		ShaderProgram* CreateShaderProgram(const char*** sources, const ShaderType* types, const unsigned short count);
		ShaderProgram* CreateShaderProgram(const std::vector<const char**>& sources, const std::vector<ShaderType>& types);
		ShaderProgram* CreateShaderProgram(Shader** shaders, const unsigned short count);
	private:
	};
}