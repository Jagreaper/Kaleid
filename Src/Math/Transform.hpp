#pragma once

#include "stdafx.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Math
{
	class KALEID_MATH_API Transform sealed
	{
	public:
		Transform();
		~Transform();

		void TranslateRelative(Vector3f& position);
		void RotateRelative(Vector3f& rotation);
		void ScaleRelative(Vector3f& scale);

		void SetRelativePosition(Vector3f& position);
		void SetRelativeRotation(Vector3f& rotation);
		void SetRelativeScale(Vector3f& scale);
		void SetWorldPosition(Vector3f& position);
		void SetWorldRotation(Vector3f& rotation);
		void SetWorldScale(Vector3f& scale);

		Vector3f GetRelativePosition();
		Vector3f GetRelativeRotation();
		Vector3f GetRelativeScale();
		Vector3f GetWorldPosition();
		Vector3f GetWorldRotation();
		Vector3f GetWorldScale();

		Transform* GetParent();

		Matrix4f GetModelMatrix();

		void AttachParent(Transform*& parent);
		void AttachChild(Transform*& child);
		void DettachParent(Transform*& parent);
		void DettachChild(Transform*& child);
	private:
		Vector3f _r_position;
		Vector3f _r_rotation;
		Vector3f _r_scale;

		Vector3f _w_position;
		Vector3f _w_rotation;
		Vector3f _w_scale;

		Matrix4f _model_matrix;

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