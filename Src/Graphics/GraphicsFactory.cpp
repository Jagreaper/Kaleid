#include "stdafx.hpp"
#include "GraphicsFactory.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool GraphicsFactory::_glfw_created = false;
bool GraphicsFactory::_glew_created = false;
std::vector<Window*> GraphicsFactory::_windows;

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

	GraphicsFactory::_windows.clear();

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
	glewInit();

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
	GraphicsFactory::_windows.push_back(window);
	return window;
}

Shader* GraphicsFactory::CreateShader(const char** source, const ShaderType type)
{
	this->Validate();

	return new Shader(source, type);
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(const std::vector<Shader*>& shaders, const std::vector<ShaderType>& types)
{
	this->Validate();

	ShaderProgram* program = new ShaderProgram();
	program->Attach(shaders);
	program->Link();
	program->Dettach(shaders);
	return program;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(Shader** shaders, const unsigned short count)
{
	this->Validate();

	ShaderProgram* program = new ShaderProgram();
	program->Attach(shaders, count);
	program->Link();
	program->Dettach(shaders, count);
	return program;
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage)
{
	this->Validate();

	VertexBuffer* buffer = new VertexBuffer();
	buffer->BufferData(data, count, point_size, usage);
	return buffer;
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage)
{
	this->Validate();

	IndexBuffer* buffer = new IndexBuffer();
	buffer->BufferData(data, count, usage);
	return buffer;
}

void GraphicsFactory::FreeWindow(Window* window)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_windows, window);

	window->Dispose();
	delete window;
}