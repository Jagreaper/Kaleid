#pragma once

#include "Vertex.hpp"
#include <vector>

namespace Kaleid::Geometry
{
	template<class T>
	class Face
	{
	public:
		inline void AddVerticies(Vertex<T>& vertex)
		{
			this->_verticies.push_back(vertex);
		}

		inline void SetVerticies(std::vector<Vertex<T>>& verticies)
		{
			this->_verticies = verticies;
		}

		inline std::vector<Vertex<T>>& GetVerticies()
		{
			return this->_verticies;
		}

		inline std::vector<Vertex<T>> GetVerticies() const
		{
			return this->_verticies;
		}
	protected:
		std::vector<Vertex<T>> _verticies;
	};

	using FaceF = Face<float>;
	using FaceD = Face<double>;
	using FaceS = Face<short>;
	using FaceI = Face<int>;
	using FaceL = Face<int64_t>;
}