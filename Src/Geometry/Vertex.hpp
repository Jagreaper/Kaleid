#pragma once

#include "stdafx.hpp"
#include "GLM\glm.hpp"

namespace Kaleid::Geometry
{
	using VectorGeometry = glm::vec3;
	using VectorNormal = glm::vec3;
	using VectorTexture = glm::vec2;

	class Vertex
	{
	public:
		VectorGeometry VectorGeometry;
		VectorNormal VectorNormal;
		VectorTexture VectorTexture;
	};
}