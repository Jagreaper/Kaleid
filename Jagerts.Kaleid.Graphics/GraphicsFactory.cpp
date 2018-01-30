#include "GraphicsFactory.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "BufferBase.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"
#include "Jagerts.Felcp.Helpers/VectorHelper.hpp"
#include "Texture.hpp"

using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Felcp::Helpers;

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

#ifdef DEBUG
void GraphicsFactory::ErrorCheck()
{
	if (glGetError() != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
}
#define _ERROR_CHECK this->ErrorCheck();
#define _VALIDATE_CHECK this->Validate();
#else
#define _ERROR_CHECK
#define _VALIDATE_CHECK
#endif

#define _DISPOSE_ALL(CLASS, ARRAY) \
for (CLASS* item : GraphicsFactory::ARRAY) \
	item->Dispose(); \
GraphicsFactory::ARRAY.clear() \

void GraphicsFactory::Dispose()
{
	_DISPOSE_ALL(Window, _windows);
	_DISPOSE_ALL(Shader, _shaders);
	_DISPOSE_ALL(ShaderProgram, _shader_programs);
	_DISPOSE_ALL(VertexBuffer, _vertex_buffers);
	_DISPOSE_ALL(IndexBuffer, _index_buffers);
	_DISPOSE_ALL(Mesh, _meshes);

	if (GraphicsFactory::_glfw_created)
		glfwTerminate();

	GraphicsFactory::_glfw_created = false;
}

#undef _DISPOSE_ALL

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
	_ERROR_CHECK

	return window;

}

Shader* GraphicsFactory::CreateShader(const ShaderType type)
{
	_VALIDATE_CHECK
	Shader* shader = new Shader(type);
	GraphicsFactory::_shaders.push_back(shader);
	_ERROR_CHECK

	return shader;
}

Shader* GraphicsFactory::CreateShader(const char** source, const ShaderType type)
{
	Shader* shader = this->CreateShader(type);
	shader->SetSource(source);
	shader->Compile();
	_ERROR_CHECK

	return shader;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram()
{
	_VALIDATE_CHECK
	ShaderProgram* program = new ShaderProgram();
	GraphicsFactory::_shader_programs.push_back(program);
	_ERROR_CHECK

	return program;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(const std::vector<Shader*>& shaders, const std::vector<ShaderType>& types)
{
	ShaderProgram* program = this->CreateShaderProgram();
	program->Attach(shaders);
	program->Link();
	program->Dettach(shaders);
	_ERROR_CHECK

	return program;
}

ShaderProgram* GraphicsFactory::CreateShaderProgram(Shader** shaders, const unsigned short count)
{
	ShaderProgram* program = this->CreateShaderProgram();
	program->Attach(shaders, count);
	program->Link();
	program->Dettach(shaders, count);
	_ERROR_CHECK

	return program;
}

VertexBuffer* GraphicsFactory::CreateVertexBuffer()
{
	_VALIDATE_CHECK
	VertexBuffer* buffer = new VertexBuffer();
	GraphicsFactory::_vertex_buffers.push_back(buffer);
	_ERROR_CHECK

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
	_ERROR_CHECK

	return buffer;
}

void GraphicsFactory::CreateVertexBuffers(VertexBuffer*& buffer, const unsigned int count)
{
	_VALIDATE_CHECK
	VertexBuffer* vbo = buffer = new VertexBuffer[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_vertex_buffers.push_back(vbo++);
	_ERROR_CHECK
}

IndexBuffer* GraphicsFactory::CreateIndexBuffer()
{
	_VALIDATE_CHECK
	IndexBuffer* buffer = new IndexBuffer();
	GraphicsFactory::_index_buffers.push_back(buffer);
	_ERROR_CHECK

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
	_ERROR_CHECK

	return buffer;
}

void GraphicsFactory::CreateIndexBuffers(IndexBuffer*& buffer, const unsigned int count)
{
	_VALIDATE_CHECK
	IndexBuffer* ibo = buffer = new IndexBuffer[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_index_buffers.push_back(ibo++);
	_ERROR_CHECK
}

Mesh* GraphicsFactory::CreateMesh()
{
	_VALIDATE_CHECK
	Mesh* mesh = new Mesh();
	GraphicsFactory::_meshes.push_back(mesh);
	_ERROR_CHECK

	return mesh;
}

Mesh* GraphicsFactory::CreateMesh(IndexBuffer*& index_buffer, VertexBuffer*& vertex_buffer)
{
	std::vector<VertexBuffer*> vertex_buffers;
	vertex_buffers.push_back(vertex_buffer);
	_ERROR_CHECK

	return this->CreateMesh(index_buffer, &vertex_buffers);
}

Mesh* GraphicsFactory::CreateMesh(IndexBuffer*& index_buffer, std::vector<VertexBuffer*>* vertex_buffers)
{
	Mesh* mesh = this->CreateMesh();
	mesh->SetIndexBuffer(index_buffer);
	mesh->SetVertexBuffers(vertex_buffers);
	_ERROR_CHECK

	return mesh;
}

void GraphicsFactory::CreateMeshes(Mesh*& meshes, const unsigned int count)
{
	_VALIDATE_CHECK
	Mesh* i_meshes = meshes = new Mesh[count];
	for (unsigned int index = 0; index < count; index++)
		GraphicsFactory::_meshes.push_back(i_meshes++);
	_ERROR_CHECK
}

Texture* GraphicsFactory::CreateTexture()
{
	_VALIDATE_CHECK
	Texture* texture = new Texture();
	GraphicsFactory::_textures.push_back(texture);
	_ERROR_CHECK

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
	_ERROR_CHECK
}

void GraphicsFactory::FreeShaderProgram(ShaderProgram* shader_program)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_shader_programs, shader_program);

	shader_program->Dispose();
	delete shader_program;
	_ERROR_CHECK
}

void GraphicsFactory::FreeVertexBuffer(VertexBuffer* vertex_buffer)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_vertex_buffers, vertex_buffer);

	vertex_buffer->Dispose();
	delete vertex_buffer;
	_ERROR_CHECK
}

void GraphicsFactory::FreeVertexBuffers(std::vector<VertexBuffer*>& vertex_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)vertex_buffers.size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers[index];
		this->FreeVertexBuffer(vbo);
		_ERROR_CHECK
	}
}

void GraphicsFactory::FreeVertexBuffers(const std::vector<VertexBuffer*>* vertex_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)vertex_buffers->size(); index++)
	{
		VertexBuffer* vbo = vertex_buffers->at(index);
		this->FreeVertexBuffer(vbo);
		_ERROR_CHECK
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
	_ERROR_CHECK
}

void GraphicsFactory::FreeIndexBuffer(IndexBuffer* index_buffer)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_index_buffers, index_buffer);

	index_buffer->Dispose();
	delete index_buffer;
	_ERROR_CHECK
}

void GraphicsFactory::FreeIndexBuffers(std::vector<IndexBuffer*>& index_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)index_buffers.size(); index++)
	{
		IndexBuffer* ibo = index_buffers[index];
		this->FreeIndexBuffer(ibo);
		_ERROR_CHECK
	}
}

void GraphicsFactory::FreeIndexBuffers(const std::vector<IndexBuffer*>* index_buffers)
{
	for (unsigned int index = 0; index < (unsigned int)index_buffers->size(); index++)
	{
		IndexBuffer* ibo = index_buffers->at(index);
		this->FreeIndexBuffer(ibo);
		_ERROR_CHECK
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
	_ERROR_CHECK
}

void GraphicsFactory::FreeMesh(Mesh*& mesh)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_meshes, mesh);

	mesh->Dispose();
	delete mesh;
	_ERROR_CHECK
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
	_ERROR_CHECK
}

void GraphicsFactory::FreeTexture(TextureBase*& texture)
{
	VectorHelper::RemoveItem(&GraphicsFactory::_textures, texture);

	texture->Dispose();
	delete texture;
	_ERROR_CHECK
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
	_ERROR_CHECK
}

#undef _VALIDATE_CHECK
#undef _ERROR_CHECK