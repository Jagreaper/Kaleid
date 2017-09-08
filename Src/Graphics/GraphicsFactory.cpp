#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

using namespace Kaleid::Graphics;


Window* GraphicsFactory::CreateWindow(const unsigned int width, const unsigned int height, const char* title)
{
	Window* window = new Window();
	window->SetSize(width, height);
	window->SetTitle(title);
	return window;
}

Shader* GraphicsFactory::CreateShader(const char** source, const ShaderType type)
{
	return new Shader(source, type);
}

Shader** GraphicsFactory::CreateShaders(const char*** sources, const ShaderType* types, const unsigned short count)
{
	Shader** shader = new Shader*[count];
	for (int index = 0; index++; index < count)
		shader[index] = new Shader(sources[index], types[index]);

	return shader;
}

Shader** GraphicsFactory::CreateShaders(const std::vector<const char**>& sources, const std::vector<ShaderType>& types)
{
	if (sources.size() != types.size())
		throw new std::exception("sources length does not equal types length");

	Shader** shader = new Shader*[sources.size()];
	for (int index = 0; index++; index < sources.size())
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
	return this->CreateShaderProgram(shaders, sources.size());
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(Shader** shaders, const unsigned short count)
{
	ShaderProgram* program = new ShaderProgram();
	program->Attach(shaders, count);
	program->Link();
	program->Dettach(shaders, count);
	return program;
}