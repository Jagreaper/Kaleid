#pragma once

#include "stdafx.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class Window;
	class Shader;
	class ShaderProgram;
	class VertexBuffer;
	class IndexBuffer;
	class Mesh;
	class Texture;
	class TextureBase;

	enum ShaderType;
	enum BufferUsage;

	class KALEID_GRAPHICS_API GraphicsFactory sealed
	{
	public:
		GraphicsFactory();
		~GraphicsFactory();

		Window* CreateWindow(const unsigned int width, const unsigned int height, const char* title);

		Shader* CreateShader(const ShaderType type);
		Shader* CreateShader(const char** source, const ShaderType type);

	    ShaderProgram* CreateShaderProgram();
		ShaderProgram* CreateShaderProgram(const std::vector<Shader*>& shaders, const std::vector<ShaderType>& types);
		ShaderProgram* CreateShaderProgram(Shader** shaders, const unsigned short count);

		VertexBuffer* CreateVertexBuffer();
		VertexBuffer* CreateVertexBuffer(const float* data, size_t count, unsigned int stride);
		VertexBuffer* CreateVertexBuffer(const float* data, size_t count, unsigned int stride, BufferUsage usage);
		void CreateVertexBuffers(VertexBuffer*& buffer, const unsigned int count);

		IndexBuffer* CreateIndexBuffer();
		IndexBuffer* CreateIndexBuffer(const unsigned int* data, size_t count);
		IndexBuffer* CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage);
		void CreateIndexBuffers(IndexBuffer*& buffer, const unsigned int count);

		Mesh* CreateMesh();
		Mesh* CreateMesh(IndexBuffer*& index_buffer, VertexBuffer*& vertex_buffer);
		Mesh* CreateMesh(IndexBuffer*& index_buffer, std::vector<VertexBuffer*>* vertex_buffers);
		void CreateMeshes(Mesh*& meshes, const unsigned int count);

		Texture* CreateTexture();

		void FreeWindow(Window* window);
		void FreeShader(Shader* shader);
		void FreeShaderProgram(ShaderProgram* shader_program);
		void FreeVertexBuffer(VertexBuffer* vertex_buffer);
		void FreeVertexBuffers(std::vector<VertexBuffer*>& vertex_buffers);
		void FreeVertexBuffers(const std::vector<VertexBuffer*>* vertex_buffers);
		void FreeVertexBuffers(VertexBuffer*& vertex_buffers, const unsigned int count);
		void FreeIndexBuffer(IndexBuffer* index_buffer);
		void FreeIndexBuffers(std::vector<IndexBuffer*>& index_buffers);
		void FreeIndexBuffers(const std::vector<IndexBuffer*>* index_buffers);
		void FreeIndexBuffers(IndexBuffer*& index_buffers, const unsigned int count);
		void FreeMesh(Mesh*& mesh);
		void FreeMeshes(Mesh*& meshes, const unsigned int count);
		void FreeTexture(TextureBase*& texture);
		void FreeTextures(TextureBase*& textures, const unsigned int count);
	private:
#ifdef DEBUG
		void ErrorCheck();
#endif
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
		static std::vector<TextureBase*> _textures;
	};
}
API_END