#pragma once

#include "stdafx.hpp"
#include "GLM\glm.hpp"

namespace Kaleid::Math
{
	template<class T>
	using Matrix2 = glm::tmat2x2<T, glm::precision::highp>;

	template<class T>
	using Matrix3 = glm::tmat3x3<T, glm::precision::highp>;

	template<class T>
	using Matrix4 = glm::tmat4x4<T, glm::precision::highp>;

	using Matrix2f = Matrix2<float>;
	using Matrix3f = Matrix3<float>;
	using Matrix4f = Matrix4<float>;

	using Matrix2d = Matrix2<double>;
	using Matrix3d = Matrix3<double>;
	using Matrix4d = Matrix4<double>;

	using Matrix2s = Matrix2<short>;
	using Matrix3s = Matrix3<short>;
	using Matrix4s = Matrix4<short>;

	using Matrix2i = Matrix2<int>;
	using Matrix3i = Matrix3<int>;
	using Matrix4i = Matrix4<int>;

	using Matrix2l = Matrix2<int64_t>;
	using Matrix3l = Matrix3<int64_t>;
	using Matrix4l = Matrix4<int64_t>;
}