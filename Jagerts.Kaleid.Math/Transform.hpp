#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Matrix.hpp"
#include "Jagerts.Kaleid.Math/Vector.hpp"
#include <vector>

#define jkmUsingTransformableObject using Jagerts::Kaleid::Math::TransformableObject::GetTransform

namespace Jagerts::Kaleid::Math
{
	class JAGERTS_KALEID_MATH_API Transform
	{
	public:
		Transform();
		~Transform();

		void TranslateRelative(const Vector3F& position);
		void RotateRelative(const Vector3F& rotation);
		void ScaleRelative(const Vector3F& scale);

		void TranslateRelative(const float& x, const float& y, const float& z);
		void RotateRelative(const float& x, const float& y, const float& z);
		void ScaleRelative(const float& x, const float& y, const float& z);

		void SetRelativePosition(const Vector3F& position);
		void SetRelativeRotation(const Vector3F& rotation);
		void SetRelativeScale(const Vector3F& scale);
		void SetWorldPosition(const Vector3F& position);
		void SetWorldRotation(const Vector3F& rotation);
		void SetWorldScale(const Vector3F& scale);

		void SetRelativePosition(const float& x, const float& y, const float& z);
		void SetRelativeRotation(const float& x, const float& y, const float& z);
		void SetRelativeScale(const float& x, const float& y, const float& z);
		void SetWorldPosition(const float& x, const float& y, const float& z);
		void SetWorldRotation(const float& x, const float& y, const float& z);
		void SetWorldScale(const float& x, const float& y, const float& z);

		Vector3F& GetRelativePosition();
		Vector3F& GetRelativeRotation();
		Vector3F& GetRelativeScale();
		Vector3F& GetWorldPosition();
		Vector3F& GetWorldRotation();
		Vector3F& GetWorldScale();

		const Vector3F& GetRelativePosition() const;
		const Vector3F& GetRelativeRotation() const;
		const Vector3F& GetRelativeScale() const;
		const Vector3F& GetWorldPosition() const;
		const Vector3F& GetWorldRotation() const;
		const Vector3F& GetWorldScale() const;

		Transform const* GetParent() const;

		Matrix4F& GetModelMatrix();
		const Matrix4F& GetModelMatrix() const;

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
		Vector3F RotateRelativeByWorld(const Vector3F& p_rotation, const Vector3F& r_postion);
	};

	class JAGERTS_KALEID_MATH_API TransformableObject
	{
	public:
		Jagerts::Kaleid::Math::Transform* GetTransform();
	protected:
		Jagerts::Kaleid::Math::Transform _transform;
	};
}