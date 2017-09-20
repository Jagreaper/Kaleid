#pragma once

#include "stdafx.hpp"
#include "GLM\glm.hpp"

namespace Kaleid::Math
{
	template<class T>
	using Vector2 = glm::tvec2<T, glm::precision::highp>;

	template<class T>
	using Vector3 = glm::tvec3<T, glm::precision::highp>;

	template<class T>
	using Vector4 = glm::tvec4<T, glm::precision::highp>;

	using Vector2F = Vector2<float>;
	using Vector3F = Vector3<float>;
	using Vector4F = Vector4<float>;

	using Vector2D = Vector2<double>;
	using Vector3D = Vector3<double>;
	using Vector4D = Vector4<double>;

	using Vector2S = Vector2<short>;
	using Vector3S = Vector3<short>;
	using Vector4S = Vector4<short>;

	using Vector2I = Vector2<int>;
	using Vector3I = Vector3<int>;
	using Vector4I = Vector4<int>;

	using Vector2L = Vector2<int64_t>;
	using Vector3L = Vector3<int64_t>;
	using Vector4L = Vector4<int64_t>;
}