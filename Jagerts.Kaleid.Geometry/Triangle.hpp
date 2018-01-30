#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Geometry/Face.hpp"

namespace Jagerts::Kaleid::Geometry
{
	class JAGERTS_KALEID_GEOMETRY_API Triangle : public FaceF
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