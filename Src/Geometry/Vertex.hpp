#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"
#include "Nullable.hpp"

namespace Kaleid::Geometry
{
	using VectorGeometry = Kaleid::Helpers::Nullable<Kaleid::Math::Vector3f>;
	using VectorNormal = Kaleid::Helpers::Nullable<Kaleid::Math::Vector3f>;
	using VectorTexture = Kaleid::Helpers::Nullable<Kaleid::Math::Vector2f>;

	class Vertex
	{
	public:
		VectorGeometry VectorGeometry;
		VectorNormal VectorNormal;
		VectorTexture VectorTexture;
	};
}