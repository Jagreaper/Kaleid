#include "stdafx.hpp"
#include "Quad.hpp"
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "GraphicsFactory.hpp"

using namespace Kaleid::Math;
using namespace Kaleid::Graphics;
using namespace Kaleid::Game;

Mesh* Quad::_mesh = NULL;

Quad::Quad()
{
	this->_shader_program = NULL;
}

void Quad::Render(Renderer*& renderer, std::function<void(ShaderProgram*&)> arguments)
{
	renderer->RenderMesh(this->_mesh, this->_shader_program, NULL, arguments);
}

void Quad::SetShaderProgram(ShaderProgram*& shader_program)
{
	this->_shader_program = shader_program;
}

ShaderProgram* Quad::GetShaderProgram()
{
	return this->_shader_program;
}


bool Quad::MeshExists()
{
	return Quad::_mesh != NULL;
}

Kaleid::Graphics::Mesh* Quad::CreateMesh(GraphicsFactory*& graphics_factory)
{
	if (Quad::_mesh == NULL)
	{
		const float verticies[] =
		{
			-1.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f,
		};

		const unsigned int indicies[] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		VertexBuffer* vertex_buffer = graphics_factory->CreateVertexBuffer(verticies, 24, 3);
		IndexBuffer* index_buffer = graphics_factory->CreateIndexBuffer(indicies, 36);
		Quad::_mesh = graphics_factory->CreateMesh(index_buffer, vertex_buffer);
		Quad::_mesh->Compose();
		return Quad::GetMesh();
	}
}

Kaleid::Graphics::Mesh* Quad::GetMesh()
{
	return Quad::_mesh;
}

void Quad::FreeMesh(GraphicsFactory*& graphics_factory)
{
	graphics_factory->FreeIndexBuffer(Quad::_mesh->GetIndexBuffer());
	graphics_factory->FreeVertexBuffers(Quad::_mesh->GetVertexBuffers());
	graphics_factory->FreeMesh(Quad::_mesh);
}