#pragma once

#include "stdafx.hpp"
#include "Face.hpp"

namespace Kaleid::Geometry
{
	template<class T>
	class Shape
	{
	public:
		inline void SetFaces(std::vector<Face<T>>& faces)
		{
			this->_faces = faces;
		}

		inline std::vector<Face<T>>& GetFaces()
		{
			return this->_faces;
		}

		inline std::vector<Face<T>> GetFaces() const
		{
			return this->_faces;
		}
	private:
		std::vector<Face<T>> _faces;
	};

	using ShapeF = Shape<float>;
	using ShapeD = Shape<double>;
	using ShapeS = Shape<short>;
	using ShapeI = Shape<int>;
	using ShapeL = Shape<int64_t>;
}