#pragma once

#include "stdafx.hpp"
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "BufferBase.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Kaleid::Graphics
{
	class GraphicsFactory
	{
	public:
		KALEID_GRAPHICS_API GraphicsFactory();
		KALEID_GRAPHICS_API ~GraphicsFactory();
		KALEID_GRAPHICS_API Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);
		KALEID_GRAPHICS_API Shader* CreateShader(const char** source, const ShaderType type);
		KALEID_GRAPHICS_API Shader** CreateShaders(const char*** sources, const ShaderType* types, const unsigned short count);
		KALEID_GRAPHICS_API Shader** CreateShaders(const std::vector<const char**>& sources, const std::vector<ShaderType>& types);
		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram(const char*** sources, const ShaderType* types, const unsigned short count);
		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram(const std::vector<const char**>& sources, const std::vector<ShaderType>& types);
		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram(Shader** shaders, const unsigned short count);
		KALEID_GRAPHICS_API VertexBuffer* CreateVertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		KALEID_GRAPHICS_API IndexBuffer* CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);

		KALEID_GRAPHICS_API void FreeWindow(Window* window);
#ifdef KALEID_GRAPHICS_DLL
	private:
		static void Dispose();
		static void Validate();
		static void InitGLFW();
		static void InitGLEW();

		static bool _glfw_created;
		static bool _glew_created;
		static unsigned int _count;

		static std::vector<Window*> _windows;
#endif
	};
}