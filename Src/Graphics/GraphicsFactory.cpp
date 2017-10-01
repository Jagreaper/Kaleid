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
	window->SetSize(width, height);
	window->SetTitle(title);
	window->MakeCurrent();
	GraphicsFactory::_windows.push_back(window);

	this->Validate();

#ifdef DEBUG
	this->ErrorCheck();
#endif

	return window;

}

Shader* GraphicsFactory::CreateShader(const ShaderType type)
{
	this->Validate();

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
	this->Validate();

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
	this->Validate();

	VertexBuffer* buffer = new VertexBuffer();
	GraphicsFactory::_vertex_buffers.push_back(buffer);

#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float* data, size_t count, unsigned int point_size)
{
	return this->CreateVertexBuffer(data, count, point_size, BufferUsage::StaticDraw);
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage)
{
	VertexBuffer* buffer = this->CreateVertexBuffer();
	buffer->BufferData(data, count, point_size, usage);

#ifdef DEBUG
	this->ErrorCheck();
#endif

	return buffer;
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer()
{
	this->Validate();

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

Mesh* GraphicsFactory::CreateMesh()
{
	this->Validate();

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

void GraphicsFactory::FreeWindow(Window* window)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_windows, window);

	window->Dispose();
	delete window;

#ifdef DEBUG
	this->ErrorCheck();
#endif
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
	for (int index = 0; index < vertex_buffers.size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers[index];
		this->FreeVertexBuffer(vbo);

		VectorHelper::RemoveItem(&GraphicsFactory::_vertex_buffers, vbo);
		delete vbo;

#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeVertexBuffers(const std::vector<VertexBuffer*>* vertex_buffers)
{
	for (int index = 0; index < vertex_buffers->size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers->at(index);
		this->FreeVertexBuffer(vbo);

		VectorHelper::RemoveItem(&GraphicsFactory::_vertex_buffers, vbo);
		delete vbo;

#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
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
	for (int index = 0; index < index_buffers.size(); index++)
	{
		IndexBuffer* ibo = index_buffers[index];
		this->FreeIndexBuffer(ibo);

		VectorHelper::RemoveItem(&GraphicsFactory::_index_buffers, ibo);
		delete ibo;

#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
}

void GraphicsFactory::FreeIndexBuffers(const std::vector<IndexBuffer*>* index_buffers)
{
	for (int index = 0; index < index_buffers->size(); index++)
	{
		IndexBuffer* ibo = index_buffers->at(index);
		this->FreeIndexBuffer(ibo);

		VectorHelper::RemoveItem(&GraphicsFactory::_index_buffers, ibo);
		delete ibo;

#ifdef DEBUG
		this->ErrorCheck();
#endif
	}
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

#ifdef DEBUG

void GraphicsFactory::ErrorCheck()
{
	if (glGetError() != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
}

#endif