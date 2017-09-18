#pragma once

#include "stdafx.hpp"
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "BufferBase.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"


API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory sealed
	{
	public:
		KALEID_GRAPHICS_API GraphicsFactory();
		KALEID_GRAPHICS_API ~GraphicsFactory();

		KALEID_GRAPHICS_API Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);

		KALEID_GRAPHICS_API Shader* CreateShader(const ShaderType type);
		KALEID_GRAPHICS_API Shader* CreateShader(const char** source, const ShaderType type);

		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram();
		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram(const std::vector<Shader*>& shaders, const std::vector<ShaderType>& types);
		KALEID_GRAPHICS_API ShaderProgram* CreateShaderProgram(Shader** shaders, const unsigned short count);

		KALEID_GRAPHICS_API VertexBuffer* CreateVertexBuffer();
		KALEID_GRAPHICS_API VertexBuffer* CreateVertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);

		KALEID_GRAPHICS_API IndexBuffer* CreateIndexBuffer();
		KALEID_GRAPHICS_API IndexBuffer* CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);

		KALEID_GRAPHICS_API Mesh* CreateMesh();
		KALEID_GRAPHICS_API Mesh* CreateMesh(IndexBuffer*& index_buffer, std::vector<VertexBuffer*>* vertex_buffers);

		KALEID_GRAPHICS_API void FreeWindow(Window*& window);
		KALEID_GRAPHICS_API void FreeShader(Shader*& shader);
		KALEID_GRAPHICS_API void FreeShaderProgram(ShaderProgram*& shader_program);
		KALEID_GRAPHICS_API void FreeVertexBuffer(VertexBuffer*& vertex_buffer);
		KALEID_GRAPHICS_API void FreeIndexBuffer(IndexBuffer*& index_buffer);
		KALEID_GRAPHICS_API void FreeMesh(Mesh*& mesh);
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
		static std::vector<Shader*> _shaders;
		static std::vector<ShaderProgram*> _shader_programs;
		static std::vector<VertexBuffer*> _vertex_buffers;
		static std::vector<IndexBuffer*> _index_buffers;
		static std::vector<Mesh*> _meshes;
#endif
	};
}
API_END