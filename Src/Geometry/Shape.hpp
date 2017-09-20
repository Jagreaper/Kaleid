#pragma once

#include "stdafx.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Geometry
{
	class Face;

	class KALEID_GEOMETRY_API Shape
	{
	public:
		void SetFaces(std::vector<Face>& faces);
		std::vector<Face>& GetFaces();
		std::vector<Face> GetFaces() const;
	private:
		std::vector<Face> _faces;
	};
}
API_END