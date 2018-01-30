#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Game/Model.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"
#include <vector>
#include <unordered_map>

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API Actor : public Jagerts::Kaleid::Game::ModelObject
	{
	public:
		jkgUsingModelObject;
	};
}