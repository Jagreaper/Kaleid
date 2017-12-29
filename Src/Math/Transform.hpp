#pragma once

#include "stdafx.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <vector>

namespace Kaleid::Math
{
	class KALEID_MATH_API Transform sealed
	{
	public:
		Transform();
		~Transform();

		void TranslateRelative(Vector3F& position);
		void RotateRelative(Vector3F& rotation);
		void ScaleRelative(Vector3F& scale);

		void SetRelativePosition(Vector3F& position);
		void SetRelativeRotation(Vector3F& rotation);
		void SetRelativeScale(Vector3F& scale);
		void SetWorldPosition(Vector3F& position);
		void SetWorldRotation(Vector3F& rotation);
		void SetWorldScale(Vector3F& scale);

		Vector3F GetRelativePosition();
		Vector3F GetRelativeRotation();
		Vector3F GetRelativeScale();
		Vector3F GetWorldPosition();
		Vector3F GetWorldRotation();
		Vector3F GetWorldScale();

		Transform* GetParent();

		Matrix4F GetModelMatrix();

		void AttachParent(Transform* parent);
		void AttachChild(Transform* child);
		void DettachParent(Transform* parent);
		void DettachChild(Transform* child);
	private:
		Vector3F _r_position;
		Vector3F _r_rotation;
		Vector3F _r_scale;

		Vector3F _w_position;
		Vector3F _w_rotation;
		Vector3F _w_scale;

		Matrix4F _model_matrix;

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

	class KALEID_GAME_API TransformableObject
	{
	public:
		Kaleid::Math::Transform* GetTransform();
	protected:
		Kaleid::Math::Transform _transform;
	};
}