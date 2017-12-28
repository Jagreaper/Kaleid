#pragma once
#pragma once;

#include "stdafx.hpp"
#include "Face.hpp"

API_BEGIN
namespace Kaleid::Geometry
{
	class KALEID_GEOMETRY_API Triangle : public FaceF
	{
	public:
		Triangle();
		Triangle(VertexF& v1, VertexF& v2, VertexF& v3);

		void SetP1(VertexF& ver);
		void SetP2(VertexF& ver);
		void SetP3(VertexF& ver);

		VertexF& GetP1();
		VertexF GetP1() const;
		VertexF& GetP2();
		VertexF GetP2() const;
		VertexF& GetP3();
		VertexF GetP3() const;
	};
}
API_END