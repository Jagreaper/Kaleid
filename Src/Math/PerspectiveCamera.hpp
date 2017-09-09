#pragma once

#include "stdafx.hpp"
#include "CameraBase.hpp"

namespace Kaleid::Math
{
	class PerspectiveCamera sealed : public CameraBase
	{
	public:
		KALEID_MATH_API PerspectiveCamera();

		KALEID_MATH_API float GetFov() const;
		KALEID_MATH_API void SetFov(float fov);

		KALEID_MATH_API float GetNearZ() const;
		KALEID_MATH_API void SetNearZ(float z_near);

		KALEID_MATH_API float GetFarZ() const;
		KALEID_MATH_API void SetFarZ(float z_far);

		KALEID_MATH_API glm::mat4 GetProjectionMatrix();
#ifdef KALEID_MATH_DLL
	private:
		float _z_near;
		float _z_far;
		float _fov;
#endif
	};
}