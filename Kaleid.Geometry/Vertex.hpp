#pragma once

#include "Kaleid.Math\Vector.hpp"
#include "Kaleid.Helpers\Nullable.hpp"

namespace Kaleid::Geometry
{
	template<class T>
	using VectorGeometry = Kaleid::Helpers::Nullable<Kaleid::Math::Vector3<T>>;

	using VectorGeometryF = VectorGeometry<float>;
	using VectorGeometryD = VectorGeometry<double>;
	using VectorGeometryS = VectorGeometry<short>;
	using VectorGeometryI = VectorGeometry<int>;
	using VectorGeometryL = VectorGeometry<int64_t>;

	template<class T>
	using VectorNormal = Kaleid::Helpers::Nullable<Kaleid::Math::Vector3<T>>;

	using VectorNormalF = VectorNormal<float>;
	using VectorNormalD = VectorNormal<double>;
	using VectorNormalS = VectorNormal<short>;
	using VectorNormalI = VectorNormal<int>;
	using VectorNormalL = VectorNormal<int64_t>;

	template<class T>
	using VectorTexture = Kaleid::Helpers::Nullable<Kaleid::Math::Vector2<T>>;

	using VectorTextureF = VectorTexture<float>;
	using VectorTextureD = VectorTexture<double>;
	using VectorTextureS = VectorTexture<short>;
	using VectorTextureI = VectorTexture<int>;
	using VectorTextureL = VectorTexture<int64_t>;

	template<class T>
	class Vertex
	{
	public:
		VectorGeometry<T> VectorGeometry;
		VectorNormal<T> VectorNormal;
		VectorTexture<T> VectorTexture;
	};

	using VertexF = Vertex<float>;
	using VertexD = Vertex<double>;
	using VertexS = Vertex<short>;
	using VertexI = Vertex<int>;
	using VertexL = Vertex<int64_t>;
}