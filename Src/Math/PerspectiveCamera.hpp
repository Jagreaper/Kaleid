#pragma once

#include "stdafx.hpp"
#include "CameraBase.hpp"

namespace Kaleid::Math
{
	class KALEID_MATH_API PerspectiveCamera : public CameraBase
	{
	public:
		PerspectiveCamera();

		float GetFov() const;
		void SetFov(float fov);

		float GetNearZ() const;
		void SetNearZ(float z_near);

		float GetFarZ() const;
		void SetFarZ(float z_far);

		Matrix4F GetProjectionMatrix();
		bool IsPerspective();
		bool IsOrthographic();
	private:
		float _z_near;
		float _z_far;
		float _fov;
	};
}