#include "stdafx.hpp"
#include "Model.hpp"
#include "VectorHelper.hpp"
#include "Renderer.hpp"

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

void Model::AddComponent(ModelComponent component)
{
	component.GetTransform()->AttachParent(&this->_transform);
	this->_model_components.push_back(component);
}

void Model::AddComponents(std::vector<ModelComponent>& components)
{
	for (int index = 0; index < components.size(); index++)
		components[index].GetTransform()->AttachParent(&this->_transform);

	VectorHelper::AddRange(this->_model_components, components);
}

void Model::RemoveComponent(const std::string name)
{
	int pos = 0;
	for (int index = 0; index < this->_model_components.size(); index++)
	{
		if (this->_model_components[index].GetName() == name)
		{
			pos = index;
			break;
		}

		if (index == this->_model_components.size() - 1)
			return;
	}

	this->RemoveComponent(pos);
}

void Model::RemoveComponent(int index)
{
	if (index < this->_model_components.size())
	{
		this->_model_components[index].GetTransform()->DettachParent(this->GetTransform());
		VectorHelper::Remove(this->_model_components, index);
	}
}

void Model::RemoveComponents()
{
	for (int index = 0; index < this->_model_components.size(); index++)
		this->_model_components[index].GetTransform()->DettachParent(this->GetTransform());

	this->_model_components.clear();
}

const ModelComponent* Model::GetComponent(const std::string name)
{
	for (int index = 0; index < this->_model_components.size(); index++)
	{
		if (this->_model_components[index].GetName() == name)
			return &this->_model_components[index];
	}

	return NULL;
}

const ModelComponent* Model::GetComponent(int index)
{
	if (index < this->_model_components.size())
		return &this->_model_components[index];

	return NULL;
}

std::vector<ModelComponent>* Model::GetComponents()
{
	return &this->_model_components;
}

Transform* Model::GetTransform()
{
	return &this->_transform;
}

void Model::Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(ShaderProgram*&, Material*)> arguments)
{
	for (int index = 0; index < this->_model_components.size(); index++)
		this->_model_components[index].Render(renderer, arguments);
}
