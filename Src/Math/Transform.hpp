#pragma once

#include "stdafx.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Math
{
	class KALEID_MATH_API Transform sealed
	{
	public:
		Transform();
		~Transform();

		void TranslateRelative(glm::vec3& position);
		void RotateRelative(glm::vec3& rotation);
		void ScaleRelative(glm::vec3& scale);

		void SetRelativePosition(glm::vec3& position);
		void SetRelativeRotation(glm::vec3& rotation);
		void SetRelativeScale(glm::vec3& scale);
		void SetWorldPosition(glm::vec3& position);
		void SetWorldRotation(glm::vec3& rotation);
		void SetWorldScale(glm::vec3& scale);

		glm::vec3 GetRelativePosition();
		glm::vec3 GetRelativeRotation();
		glm::vec3 GetRelativeScale();
		glm::vec3 GetWorldPosition();
		glm::vec3 GetWorldRotation();
		glm::vec3 GetWorldScale();

		Transform* GetParent();

		glm::mat4 GetModelMatrix();

		void AttachParent(Transform*& parent);
		void AttachChild(Transform*& child);
		void DettachParent(Transform*& parent);
		void DettachChild(Transform*& child);
	private:
		glm::vec3 _r_position;
		glm::vec3 _r_rotation;
		glm::vec3 _r_scale;

		glm::vec3 _w_position;
		glm::vec3 _w_rotation;
		glm::vec3 _w_scale;

		glm::mat4 _model_matrix;

		bool _is_position_dirty;
		bool _is_rotation_dirty;
		bool _is_scale_dirty;
		bool _is_model_matrix_dirty;

		Transform* _parent;
		std::vector<Transform*> _children;

		void MarkPositionDirty();
		void MarkRotationDirty();
		void MarkScaleDirty();
	};
}
API_END