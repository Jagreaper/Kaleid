#pragma once

#include "stdafx.hpp"
#include "Vertex.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Geometry
{
	class KALEID_GEOMETRY_API Face
	{
	public:
		void SetVerticies(std::vector<Vertex>& verticies);
		std::vector<Vertex>& GetVerticies();
		std::vector<Vertex> GetVerticies() const;
	private:
		std::vector<Vertex> _verticies;
	};
}
API_END