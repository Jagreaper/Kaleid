#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Math\Transform.hpp"
#include "Jagerts.Kaleid.Graphics\Renderer.hpp"
#include "Model.hpp"
#include <vector>

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API Terrian : public ModelObject, public Jagerts::Kaleid::Graphics::RenderableObject
	{
	public:
		Terrian(float length, float width);
	};
}