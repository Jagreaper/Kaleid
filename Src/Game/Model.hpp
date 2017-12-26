#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include "ModelComponent.hpp"
#include <functional>
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class Mesh;
	class TextureBase;
	class ShaderProgram;
	class Renderer;
}

namespace Kaleid::Game
{
	class KALEID_GAME_API Model sealed
	{
	public:
		void AddComponent(ModelComponent component);
		void AddComponents(std::vector<ModelComponent>& components);
		void RemoveComponent(const std::string name);
		void RemoveComponent(int index);
		void RemoveComponents();
		const ModelComponent* GetComponent(const std::string name);
		const ModelComponent* GetComponent(int index);
		std::vector<ModelComponent>* GetComponents();
		Kaleid::Math::Transform* GetTransform();
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&)> arguments);
	private:
		std::vector<ModelComponent> _model_components;
		Kaleid::Math::Transform _transform;
	};
}
API_END