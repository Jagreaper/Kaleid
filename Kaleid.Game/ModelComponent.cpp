#include "ModelComponent.hpp"
#include "Jagerts.Felcp.Helpers\VectorHelper.hpp"

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Jagerts::Felcp::Helpers;

std::vector<ModelComponent*> ModelComponent::_model_components;

ModelComponent* ModelComponent::AllocateMemory()
{
	ModelComponent* model_component = new ModelComponent();
	ModelComponent::_model_components.push_back(model_component);
	return model_component;
}

void ModelComponent::FreeMemory(ModelComponent*& model_component)
{
	VectorHelper::RemoveItem(ModelComponent::_model_components, model_component);
	delete model_component;
}

void ModelComponent::FreeAllMemory()
{
	for (int index = 0; index < ModelComponent::_model_components.size(); index++)
		delete ModelComponent::_model_components[index];

	ModelComponent::_model_components.clear();
}

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

Material& ModelComponent::GetMaterial()
{
	return this->_material;
}

void ModelComponent::SetMaterialInfo(const MaterialInfo material_info)
{
	this->_material_info = material_info;
	this->_material = material_info.CreateMaterial();
}

MaterialInfo& ModelComponent::GetMaterialInfo()
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
