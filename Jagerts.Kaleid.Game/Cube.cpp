#include "Cube.hpp"
#include "Jagerts.Kaleid.Graphics\Renderer.hpp"
#include "Jagerts.Kaleid.Graphics\Mesh.hpp"
#include "Jagerts.Kaleid.Graphics\GraphicsFactory.hpp"

using namespace Jagerts::Kaleid::Math;
using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Kaleid::Game;

Mesh* Cube::_mesh = NULL;

Cube::Cube()
{
	this->_shader_program = NULL;
}

void Cube::Render(Renderer*& renderer, std::function<void(ShaderProgram*&)> arguments)
{
	renderer->RenderMesh(this->_mesh, this->_shader_program, NULL, arguments);
}

void Cube::SetShaderProgram(ShaderProgram*& shader_program)
{
	this->_shader_program = shader_program;
}

ShaderProgram* Cube::GetShaderProgram()
{
	return this->_shader_program;
}


bool Cube::MeshExists()
{
	return Cube::_mesh != NULL;
}

Jagerts::Kaleid::Graphics::Mesh* Cube::CreateMesh(GraphicsFactory*& graphics_factory)
{
	if (Cube::_mesh == NULL)
	{
		const float verticies[] =
		{
			// Front
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			// Back
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
		};

		const unsigned int indicies[] =
		{
			// Front
			0, 1, 2,
			2, 3, 0,

			// Top
			1, 5, 6,
			6, 2, 1,

			// Back
			7, 6, 5,
			5, 4, 7,

			// Bottom
			4, 0, 3,
			3, 7, 4,

			// Left
			4, 5, 1,
			1, 0, 4,

			// Right
			3, 2, 6,
			6, 7, 3,
		};

		VertexBuffer* vertex_buffer = graphics_factory->CreateVertexBuffer(verticies, 24, 3);
		IndexBuffer* index_buffer = graphics_factory->CreateIndexBuffer(indicies, 36);
		Cube::_mesh = graphics_factory->CreateMesh(index_buffer, vertex_buffer);
		Cube::_mesh->Compose();
		return Cube::GetMesh();
	}
}

Jagerts::Kaleid::Graphics::Mesh* Cube::GetMesh()
{
	return Cube::_mesh;
}

void Cube::FreeMesh(GraphicsFactory*& graphics_factory)
{
	graphics_factory->FreeIndexBuffer(Cube::_mesh->GetIndexBuffer());
	graphics_factory->FreeVertexBuffers(Cube::_mesh->GetVertexBuffers());
	graphics_factory->FreeMesh(Cube::_mesh);
}