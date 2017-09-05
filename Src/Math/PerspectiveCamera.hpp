#pragma once

#include "stdafx.hpp"
#include "CameraBase.hpp"

namespace Kaleid::Math
{
	class KALEID_MATH_API PerspectiveCamera : public CameraBase
	{
	public:
		PerspectiveCamera();

		// Positon
		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);
		void TranslatePosition(const glm::vec3& offset);

		// Rotation
		const glm::vec3& GetRotation() const;
		void SetRotation(const glm::vec3& rotation);
		void TranslateRotation(const glm::vec3& offset);

		float GetFov() const;
		void SetFov(float fov);

		float GetNearZ() const;
		void SetNearZ(float z_near);

		float GetFarZ() const;
		void SetFarZ(float z_far);

		float GetAspectRatio() const;
		void SetAspectRatio(float aspect_ratio);

		glm::mat4 GetOrientation() const;

		glm::vec3 GetForward() const;
		glm::vec3 GetRight() const;
		glm::vec3 GetUp() const;

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
	private:
		void NormalizeRotation();

		glm::vec3 _position;
		glm::vec3 _rotation;

		glm::mat4 _projection_matrix;
		glm::mat4 _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _z_near;
		float _z_far;
		float _aspect_ratio;
		float _fov;
	};
}