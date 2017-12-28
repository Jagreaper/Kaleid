#pragma once

#include "stdafx.hpp"
#include "Model.hpp"
#include "Transform.hpp"
#include <vector>
#include <unordered_map>

API_BEGIN
namespace Kaleid::Game
{
	class KALEID_GAME_API Actor : public Kaleid::Game::ModelObject
	{
	public:
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&, Kaleid::Graphics::Material* material)> arguments);
	private:
	};
}
API_END