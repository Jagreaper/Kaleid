#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Math\Vector.hpp"

namespace Jagerts::Kaleid::Geometry
{
	template<class T>
	class Line
	{
		const T Interpolate(float scale)
		{
			T direction = this->_end - this->_origin;
			return this->_origin + (direction * scale);
		}

		jkGetterSetterHeaderDefinition(Origin, T, this->_origin);
	private:
		T _origin;
		T _end;
	};

	template<class T>
	using VectorLine = Line<Jagerts::Kaleid::Math::Vector3<T>>;

	using VectorLineF = Line<Jagerts::Kaleid::Math::Vector3F>;
	using VectorLineD = Line<Jagerts::Kaleid::Math::Vector3D>;
	using VectorLineS = Line<Jagerts::Kaleid::Math::Vector3S>;
	using VectorLineI = Line<Jagerts::Kaleid::Math::Vector3I>;
	using VectorLineL = Line<Jagerts::Kaleid::Math::Vector3L>;
}