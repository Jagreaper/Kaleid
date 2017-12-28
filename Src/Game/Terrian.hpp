#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include <vector>

namespace Kaleid::Game
{
	class KALEID_GAME_API Terrian : public Kaleid::Math::TransformableObject
	{
	public:
		Terrian(float length, float width);
	private:
		Model* _model;
	};
}