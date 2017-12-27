#include "stdafx.hpp"
#include "Actor.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Math;
using namespace Kaleid::Helpers;
using namespace Kaleid::Graphics;

void Actor::AddModel(const char* name, Model& model)
{
	model.GetTransform()->AttachParent(this->GetTransform());
	this->_models[name] = model;
}

void Actor::RemoveModel(const char* name)
{
	this->_models[name].GetTransform()->DettachParent(this->GetTransform());
	this->_models.erase(name);
}

void Actor::RemoveModels()
{
	for (std::pair<const char*, Model> element : this->_models)
		element.second.GetTransform()->DettachParent(this->GetTransform());

	this->_models.clear();
}

Transform* Actor::GetTransform()
{
	return &this->_transform;
}

void Actor::Render(Renderer*& renderer, std::function<void(ShaderProgram*&, Material* material)> arguments)
{
	for (std::pair<const char*, Model> element : this->_models)
		element.second.Render(renderer, arguments);
}