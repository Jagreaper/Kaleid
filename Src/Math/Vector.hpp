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

	using Vector2f = Vector2<float>;
	using Vector3f = Vector3<float>;
	using Vector4f = Vector4<float>;

	using Vector2d = Vector2<double>;
	using Vector3d = Vector3<double>;
	using Vector4d = Vector4<double>;

	using Vector2s = Vector2<short>;
	using Vector3s = Vector3<short>;
	using Vector4s = Vector4<short>;

	using Vector2i = Vector2<int>;
	using Vector3i = Vector3<int>;
	using Vector4i = Vector4<int>;

	using Vector2l = Vector2<int64_t>;
	using Vector3l = Vector3<int64_t>;
	using Vector4l = Vector4<int64_t>;
}