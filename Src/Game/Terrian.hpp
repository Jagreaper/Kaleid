#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Game
{
	class KALEID_GAME_API Terrian : public ModelObject, public Kaleid::Graphics::RenderableObject
	{
	public:
		Terrian(float length, float width);
	};
}
API_END