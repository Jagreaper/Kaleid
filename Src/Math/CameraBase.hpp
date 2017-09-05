#pragma once

#include "stdafx.hpp"

namespace Kaleid::Math
{
	class KALEID_MATH_API CameraBase abstract
	{
	public:
		virtual const glm::vec3& GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void TranslatePosition(const glm::vec3& offset) = 0;

		virtual const glm::vec3& GetRotation() const = 0;
		virtual void SetRotation(const glm::vec3& rotation) = 0;
		virtual void TranslateRotation(const glm::vec3& offset) = 0;

		virtual float GetAspectRatio() const = 0;
		virtual void SetAspectRatio(float aspect_ratio) = 0;

		virtual glm::mat4 GetOrientation() const = 0;

		virtual glm::vec3 GetForward() const = 0;
		virtual glm::vec3 GetRight() const = 0;
		virtual glm::vec3 GetUp() const = 0;

		virtual glm::mat4 GetProjectionMatrix() = 0;
		virtual glm::mat4 GetViewMatrix() = 0;
	};
}