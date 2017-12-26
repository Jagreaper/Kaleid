#include "stdafx.hpp"
#include "ModelComponent.hpp"
#include "VectorHelper.hpp"
#include "Renderer.hpp"

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;


void ModelComponent::SetMesh(Mesh*& mesh)
{
	this->_mesh = mesh;
}

const Mesh* ModelComponent::GetMesh() const
{
	return this->_mesh;
}

Mesh*& ModelComponent::GetMesh()
{
	return this->_mesh;
}

void ModelComponent::SetMaterial(const Material material)
{
	this->_material = material;
}

const Material& ModelComponent::GetMaterial() const
{
	return this->_material;
}

void ModelComponent::SetMaterialInfo(const MaterialInfo material_info)
{
	this->_material_info = material_info;
	this->_material = material_info.CreateMaterial();
}

const MaterialInfo& ModelComponent::GetMaterialInfo() const
{
	return this->_material_info;
}

void ModelComponent::SetShaderProgram(ShaderProgram*& shader_program)
{
	this->_shader_program = shader_program;
}

const ShaderProgram* ModelComponent::GetShaderProgram() const
{
	return this->_shader_program;
}

ShaderProgram*& ModelComponent::GetShaderProgram()
{
	return this->_shader_program;
}

Transform* ModelComponent::GetTransform()
{
	return &this->_transform;
}

void ModelComponent::Render(Renderer*& renderer, std::function<void(ShaderProgram*&, Material*)> arguments)
{
	renderer->RenderMesh(this->_mesh, this->_shader_program, &this->_material, arguments);
}

void ModelComponent::SetName(const std::string name)
{
	this->_name = name;
}

void ModelComponent::SetName(const char* name)
{
	this->_name = std::string(name);
}

const std::string& ModelComponent::GetName() const
{
	return this->_name;
}
