#pragma once

#include "stdafx.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Math
{
	class Transform sealed
	{
	public:
		KALEID_MATH_API Transform();
		KALEID_MATH_API ~Transform();

		KALEID_MATH_API void TranslateRelative(glm::vec3& position);
		KALEID_MATH_API void RotateRelative(glm::vec3& rotation);
		KALEID_MATH_API void ScaleRelative(glm::vec3& scale);

		KALEID_MATH_API void SetRelativePosition(glm::vec3& position);
		KALEID_MATH_API void SetRelativeRotation(glm::vec3& rotation);
		KALEID_MATH_API void SetRelativeScale(glm::vec3& scale);
		KALEID_MATH_API void SetWorldPosition(glm::vec3& position);
		KALEID_MATH_API void SetWorldRotation(glm::vec3& rotation);
		KALEID_MATH_API void SetWorldScale(glm::vec3& scale);

		KALEID_MATH_API glm::vec3 GetRelativePosition();
		KALEID_MATH_API glm::vec3 GetRelativeRotation();
		KALEID_MATH_API glm::vec3 GetRelativeScale();
		KALEID_MATH_API glm::vec3 GetWorldPosition();
		KALEID_MATH_API glm::vec3 GetWorldRotation();
		KALEID_MATH_API glm::vec3 GetWorldScale();

		KALEID_MATH_API Transform* GetParent();

		KALEID_MATH_API glm::mat4 GetModelMatrix();

		KALEID_MATH_API void AttachParent(Transform*& parent);
		KALEID_MATH_API void AttachChild(Transform*& child);
		KALEID_MATH_API void DettachParent(Transform*& parent);
		KALEID_MATH_API void DettachChild(Transform*& child);
#ifdef KALEID_MATH_DLL
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
#endif
	};
}
API_END