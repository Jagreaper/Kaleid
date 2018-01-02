#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Kaleid.Math\Transform.hpp"
#include "Kaleid.Graphics\Renderer.hpp"
#include "Model.hpp"
#include <vector>

namespace Kaleid::Game
{
	class KALEID_GAME_API Terrian : public ModelObject, public Kaleid::Graphics::RenderableObject
	{
	public:
		Terrian(float length, float width);
	};
}