#pragma once

#include "stdafx.hpp"

namespace Kaleid::Math
{
	class KALEID_MATH_API CameraBase abstract
	{
	public:
		CameraBase();

		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);
		void TranslatePosition(const glm::vec3& offset);

		const glm::vec3& GetRotation() const;
		void SetRotation(const glm::vec3& rotation);
		void TranslateRotation(const glm::vec3& offset);

		float GetAspectRatio() const;
		void SetAspectRatio(float aspect_ratio);

		glm::mat4 GetOrientation() const;

		glm::vec3 GetForward() const;
		glm::vec3 GetRight() const;
		glm::vec3 GetUp() const;

		virtual glm::mat4 GetProjectionMatrix() = 0;
		glm::mat4 GetViewMatrix();
	protected:
		void NormalizeRotation();

		glm::vec3 _position;
		glm::vec3 _rotation;

		glm::mat4 _projection_matrix;
		glm::mat4 _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _aspect_ratio;
	};
}