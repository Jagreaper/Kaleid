#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/CameraBase.hpp"

namespace Jagerts::Kaleid::Math
{
	class JAGERTS_KALEID_MATH_API OrthographicCamera : public CameraBase
	{
	public:
		OrthographicCamera();
		jkGetterSetterHeader(Left, const float);
		jkGetterSetterHeader(Right, const float);
		jkGetterSetterHeader(Top, const float);
		jkGetterSetterHeader(Bottom, const float);

		Matrix4F GetProjectionMatrix();
		bool IsPerspective();
		bool IsOrthographic();
	private:
		float _left;
		float _right;
		float _top;
		float _bottom;
	};
}