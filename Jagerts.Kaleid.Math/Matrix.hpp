#pragma once

#include "GLM/glm.hpp"

namespace Jagerts::Kaleid::Math
{
	template<class T>
	using Matrix2 = glm::tmat2x2<T, glm::precision::highp>;

	template<class T>
	using Matrix3 = glm::tmat3x3<T, glm::precision::highp>;

	template<class T>
	using Matrix4 = glm::tmat4x4<T, glm::precision::highp>;

	using Matrix2F = Matrix2<float>;
	using Matrix3F = Matrix3<float>;
	using Matrix4F = Matrix4<float>;

	using Matrix2D = Matrix2<double>;
	using Matrix3D = Matrix3<double>;
	using Matrix4D = Matrix4<double>;

	using Matrix2S = Matrix2<short>;
	using Matrix3S = Matrix3<short>;
	using Matrix4S = Matrix4<short>;

	using Matrix2I = Matrix2<int>;
	using Matrix3I = Matrix3<int>;
	using Matrix4I = Matrix4<int>;

	using Matrix2L = Matrix2<int64_t>;
	using Matrix3L = Matrix3<int64_t>;
	using Matrix4L = Matrix4<int64_t>;
}