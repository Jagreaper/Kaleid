#pragma once

#include "stdafx.hpp"
#include "Model.hpp"
#include "Transform.hpp"
#include <vector>
#include <unordered_map>

API_BEGIN
namespace Kaleid::Game
{
	class KALEID_GAME_API Actor
	{
	public:
		void AddModel(const char* name, Model& model);
		void RemoveModel(const char* name);
		void RemoveModels();
		Kaleid::Math::Transform* GetTransform();
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&, Kaleid::Graphics::Material* material)> arguments);
	private:
		Kaleid::Math::Transform _transform;
		std::unordered_map<const char*, Model> _models;
	};
}
API_END