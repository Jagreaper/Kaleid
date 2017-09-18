#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Math
{
	class CameraBase abstract
	{
	public:
		KALEID_MATH_API CameraBase();

		KALEID_MATH_API const glm::vec3& GetPosition() const;
		KALEID_MATH_API void SetPosition(const glm::vec3& position);
		KALEID_MATH_API void TranslatePosition(const glm::vec3& offset);

		KALEID_MATH_API const glm::vec3& GetRotation() const;
		KALEID_MATH_API void SetRotation(const glm::vec3& rotation);
		KALEID_MATH_API void TranslateRotation(const glm::vec3& offset);

		KALEID_MATH_API float GetAspectRatio() const;
		KALEID_MATH_API void SetAspectRatio(float aspect_ratio);

		KALEID_MATH_API glm::mat4 GetOrientation() const;

		KALEID_MATH_API glm::vec3 GetForward() const;
		KALEID_MATH_API glm::vec3 GetRight() const;
		KALEID_MATH_API glm::vec3 GetUp() const;

		KALEID_MATH_API virtual glm::mat4 GetProjectionMatrix() = 0;
		KALEID_MATH_API glm::mat4 GetViewMatrix();
	protected:
		KALEID_MATH_API void NormalizeRotation();

		glm::vec3 _position;
		glm::vec3 _rotation;

		glm::mat4 _projection_matrix;
		glm::mat4 _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _aspect_ratio;
	};
}
API_END