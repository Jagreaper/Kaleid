#include "stdafx.hpp"
#include "Model.hpp"
#include "VectorHelper.hpp"
#include "Renderer.hpp"

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;


void Model::SetMesh(Mesh*& mesh)
{
	this->_mesh = mesh;
}

Mesh* Model::GetMesh()
{
	return this->_mesh;
}

void Model::SetTextures(std::vector<TextureBase*>& textures)
{
	for each (TextureBase* const tex in textures)
		this->_textures.push_back(tex);
}

std::vector<TextureBase*>* Model::GetTextures()
{
	return &this->_textures;
}

void Model::SetShaderProgram(ShaderProgram*& shader_program)
{
	this->_shader_program = shader_program;
}

ShaderProgram* Model::GetShaderProgram()
{
	return this->_shader_program;
}

Transform* Model::GetTransform()
{
	return &this->_transform;
}

void Model::Render(Kaleid::Graphics::Renderer*& renderer, std::function<void()> arguments)
{
	renderer->RenderMesh(this->_mesh, this->_shader_program, this->_textures, arguments);
}
