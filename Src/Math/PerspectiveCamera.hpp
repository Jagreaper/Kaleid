#pragma once

#include "stdafx.hpp"
#include "CameraBase.hpp"

API_BEGIN
namespace Kaleid::Math
{
	class KALEID_MATH_API PerspectiveCamera sealed : public CameraBase
	{
	public:
		PerspectiveCamera();

		float GetFov() const;
		void SetFov(float fov);

		float GetNearZ() const;
		void SetNearZ(float z_near);

		float GetFarZ() const;
		void SetFarZ(float z_far);

		glm::mat4 GetProjectionMatrix();
	private:
		float _z_near;
		float _z_far;
		float _fov;
	};
}
API_END