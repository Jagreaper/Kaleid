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
	Window* window = new Window();
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

Shader** GraphicsFactory::CreateShaders(const char*** sources, const ShaderType* types, const unsigned short count)
{
	this->Validate();

	Shader** shader = new Shader*[count];
	for (int index = 0; index < count; index++)
		shader[index] = new Shader(sources[index], types[index]);

	return shader;
}

Shader** GraphicsFactory::CreateShaders(const std::vector<const char**>& sources, const std::vector<ShaderType>& types)
{
	this->Validate();

	if (sources.size() != types.size())
		throw new std::exception("sources length does not equal types length");

	Shader** shader = new Shader*[sources.size()];
	for (unsigned int index = 0; index < sources.size(); index++)
		shader[index] = new Shader(sources[index], types[index]);

	return shader;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(const char*** sources, const ShaderType* types, const unsigned short count)
{
	Shader** shaders = this->CreateShaders(sources, types, count);
	return this->CreateShaderProgram(shaders, count);
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(const std::vector<const char**>& sources, const std::vector<ShaderType>& types)
{
	Shader** shaders = this->CreateShaders(sources, types);
	return this->CreateShaderProgram(shaders, (unsigned int) sources.size());
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

	return new VertexBuffer(data, count, point_size, usage);
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer(const unsigned int* data, size_t count, BufferUsage usage)
{
	this->Validate();

	return new IndexBuffer(data, count, usage);
}

void GraphicsFactory::FreeWindow(Window* window)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_windows, window);

	window->Dispose();
	delete window;
}