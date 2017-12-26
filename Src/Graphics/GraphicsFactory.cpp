#include "stdafx.hpp"
#include "GraphicsFactory.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "BufferBase.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"
#include "VectorHelper.hpp"
#include "Texture.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool GraphicsFactory::_glfw_created = false;
bool GraphicsFactory::_glew_created = false;
std::vector<Window*> GraphicsFactory::_windows;
std::vector<Shader*> GraphicsFactory::_shaders;
std::vector<ShaderProgram*> GraphicsFactory::_shader_programs;
std::vector<VertexBuffer*> GraphicsFactory::_vertex_buffers;
std::vector<IndexBuffer*> GraphicsFactory::_index_buffers;
std::vector<Mesh*> GraphicsFactory::_meshes;
std::vector<TextureBase*> GraphicsFactory::_textures;

unsigned int GraphicsFactory::_count = 0;

GraphicsFactory::GraphicsFactory()
{
	if (GraphicsFactory::_count == 0)
		this->InitGLFW();

	GraphicsFactory::_count++;
}

GraphicsFactory::~GraphicsFactory()
{
	GraphicsFactory::_count--;

	if (GraphicsFactory::_count == 0)
		GraphicsFactory::Dispose();
}

void GraphicsFactory::Dispose()
{
	for each (Window* window in GraphicsFactory::_windows)
		window->Dispose();

	for each (Shader* shader in GraphicsFactory::_shaders)
		shader->Dispose();

	for each (ShaderProgram* shader_program in GraphicsFactory::_shader_programs)
		shader_program->Dispose();

	for each (VertexBuffer* vertex_buffer in GraphicsFactory::_vertex_buffers)
		vertex_buffer->Dispose();

	for each (IndexBuffer* index_buffer in GraphicsFactory::_index_buffers)
		index_buffer->Dispose();

	for each (Mesh* mesh in GraphicsFactory::_meshes)
		mesh->Dispose();

	GraphicsFactory::_windows.clear();
	GraphicsFactory::_shaders.clear();
	GraphicsFactory::_shader_programs.clear();
	GraphicsFactory::_vertex_buffers.clear();
	GraphicsFactory::_index_buffers.clear();
	GraphicsFactory::_meshes.clear();

	if (GraphicsFactory::_glfw_created)
		glfwTerminate();

	GraphicsFactory::_glfw_created = false;
}

void GraphicsFactory::InitGLFW()
{
	if (!glfwInit())
		throw std::runtime_error("Could not start GLFW3");

	GraphicsFactory::_glfw_created = true;
}

void GraphicsFactory::InitGLEW()
{
	glewExperimental = GL_TRUE;

#ifdef RELEASE
	glewInit();
#endif

#ifdef DEBUG
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("OpenGL Initilization Error");
#endif

	GraphicsFactory::_glew_created = true;
}

void GraphicsFactory::Validate()
{
	if (!GraphicsFactory::_glfw_created)
		throw std::runtime_error("GLFW3 does not exist");

	if (GraphicsFactory::_windows.size() == 0)
		throw std::runtime_error("No OpenGL surface or context exists");

	if (!GraphicsFactory::_glew_created)
		GraphicsFactory::InitGLEW();
}

Window* GraphicsFactory::CreateWindow(const unsigned int width, const unsigned int height, const char* title)
{
	Window* window = new Window(width, height, title);
	GraphicsFactory::_windows.push_back(window);

	this->Validate();
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return window;

}

Shader* GraphicsFactory::CreateShader(const ShaderType type)
{
#ifdef DEBUG
	this->Validate();
#endif
	Shader* shader = new Shader(type);
	GraphicsFactory::_shaders.push_back(shader);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return shader;
}

Shader* GraphicsFactory::CreateShader(const char** source, const ShaderType type)
{
	Shader* shader = this->CreateShader(type);
	shader->SetSource(source);
	shader->Compile();
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return shader;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram()
{
#ifdef DEBUG
	this->Validate();
#endif
	ShaderProgram* program = new ShaderProgram();
	GraphicsFactory::_shader_programs.push_back(program);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return program;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(const std::vector<Shader*>& shaders, const std::vector<ShaderType>& types)
{
	ShaderProgram* program = this->CreateShaderProgram();
	program->Attach(shaders);
	program->Link();
	program->Dettach(shaders);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return program;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(Shader** shaders, const unsigned short count)
{
	ShaderProgram* program = this->CreateShaderProgram();
	program->Attach(shaders, count);
	program->Link();
	program->Dettach(shaders, count);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return program;
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer()
{
#ifdef DEBUG
	this->Validate();
#endif
	VertexBuffer* buffer = new VertexBuffer();
	GraphicsFactory::_vertex_buffers.push_back(buffer);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float* data, size_t count, unsigned int stride)
{
	return this->CreateVertexBuffer(data, count, stride, BufferUsage::StaticDraw);
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float* data, size_t count, unsigned int stride, BufferUsage usage)
{
	VertexBuffer* buffer = this->CreateVertexBuffer();
	buffer->BufferData(data, count, stride, usage);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

void GraphicsFactory::CreateVertexBuffers(VertexBuffer*& buffer, const unsigned int count)
{
#ifdef DEBUG
	this->Validate();
#endif
	VertexBuffer* vbo = buffer = new VertexBuffer[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_vertex_buffers.push_back(vbo++);
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer()
{
#ifdef DEBUG
	this->Validate();
#endif
	IndexBuffer* buffer = new IndexBuffer();
	GraphicsFactory::_index_buffers.push_back(buffer);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer(const unsigned int* data, size_t count)
{
	return this->CreateIndexBuffer(data, count, BufferUsage::StaticDraw);
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage)
{
	IndexBuffer* buffer = this->CreateIndexBuffer();
	buffer->BufferData(data, count, usage);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

void GraphicsFactory::CreateIndexBuffers(IndexBuffer*& buffer, const unsigned int count)
{
#ifdef DEBUG
	this->Validate();
#endif
	IndexBuffer* ibo = buffer = new IndexBuffer[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_index_buffers.push_back(ibo++);
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

Mesh* GraphicsFactory::CreateMesh()
{
#ifdef DEBUG
	this->Validate();
#endif
	Mesh* mesh = new Mesh();
	GraphicsFactory::_meshes.push_back(mesh);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return mesh;
}

Mesh* GraphicsFactory::CreateMesh(IndexBuffer*& index_buffer, VertexBuffer*& vertex_buffer)
{
	std::vector<VertexBuffer*> vertex_buffers;
	vertex_buffers.push_back(vertex_buffer);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return this->CreateMesh(index_buffer, &vertex_buffers);
}

Mesh* GraphicsFactory::CreateMesh(IndexBuffer*& index_buffer, std::vector<VertexBuffer*>* vertex_buffers)
{
	Mesh* mesh = this->CreateMesh();
	mesh->SetIndexBuffer(index_buffer);
	mesh->SetVertexBuffers(vertex_buffers);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return mesh;
}

void GraphicsFactory::CreateMeshes(Mesh*& meshes, const unsigned int count)
{
#ifdef DEBUG
	this->Validate();
#endif
	Mesh* i_meshes = meshes = new Mesh[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_meshes.push_back(i_meshes++);
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

Texture* GraphicsFactory::CreateTexture()
{
#ifdef DEBUG
	this->Validate();
#endif
	Texture* texture = new Texture();
	GraphicsFactory::_textures.push_back(texture);
#ifdef DEBUG
	this->ErrorCheck();
#endif

	return texture;
}

void GraphicsFactory::FreeWindow(Window* window)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_windows, window);

	window->Dispose();
	delete window;
}

void GraphicsFactory::FreeShader(Shader* shader)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_shaders, shader);

	shader->Dispose();
	delete shader;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeShaderProgram(ShaderProgram* shader_program)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_shader_programs, shader_program);

	shader_program->Dispose();
	delete shader_program;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeVertexBuffer(VertexBuffer* vertex_buffer)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_vertex_buffers, vertex_buffer);

	vertex_buffer->Dispose();
	delete vertex_buffer;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeVertexBuffers(std::vector<VertexBuffer*>& vertex_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)vertex_buffers.size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers[index];
		this->FreeVertexBuffer(vbo);
#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeVertexBuffers(const std::vector<VertexBuffer*>* vertex_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)vertex_buffers->size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers->at(index);
		this->FreeVertexBuffer(vbo);
#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeVertexBuffers(VertexBuffer*& vertex_buffers, const unsigned int count)
{
	VertexBuffer* buffer = vertex_buffers;

	for (unsigned int index = 0; index < count; index++)
	{
		buffer->Dispose();
		VectorHelper::RemoveItem(&GraphicsFactory::_vertex_buffers, buffer);
		buffer++;
	}

	delete[] vertex_buffers;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeIndexBuffer(IndexBuffer* index_buffer)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_index_buffers, index_buffer);

	index_buffer->Dispose();
	delete index_buffer;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeIndexBuffers(std::vector<IndexBuffer*>& index_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)index_buffers.size(); index++)
	{
		IndexBuffer* ibo = index_buffers[index];
		this->FreeIndexBuffer(ibo);
#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeIndexBuffers(const std::vector<IndexBuffer*>* index_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)index_buffers->size(); index++)
	{
		IndexBuffer* ibo = index_buffers->at(index);
		this->FreeIndexBuffer(ibo);
#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeIndexBuffers(IndexBuffer*& index_buffers, const unsigned int count)
{
	IndexBuffer* buffer = index_buffers;

	for (unsigned int index = 0; index < count; index++)
	{
		buffer->Dispose();
		VectorHelper::RemoveItem(&GraphicsFactory::_index_buffers, buffer);
		buffer++;
	}

	delete[] index_buffers;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeMesh(Mesh*& mesh)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_meshes, mesh);

	mesh->Dispose();
	delete mesh;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeMeshes(Mesh*& meshes, const unsigned int count)
{
	Mesh* i_meshes = meshes;

	for (unsigned int index = 0; index < count; index++)
	{
		i_meshes->Dispose();
		VectorHelper::RemoveItem(&GraphicsFactory::_meshes, i_meshes);
		i_meshes++;
	}

	delete[] meshes;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeTexture(TextureBase*& texture)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_textures, texture);

	texture->Dispose();
	delete texture;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

void GraphicsFactory::FreeTextures(TextureBase*& textures, const unsigned int count)
{
	TextureBase* i_textures = textures;

	for (unsigned int index = 0; index < count; index++)
	{
		i_textures->Dispose();
		VectorHelper::RemoveItem(&GraphicsFactory::_textures, i_textures);
		i_textures++;
	}

	delete[] i_textures;
#ifdef DEBUG
	this->ErrorCheck();
#endif
}

#ifdef DEBUG
void GraphicsFactory::ErrorCheck()
{
	if (glGetError() != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
}
#endif