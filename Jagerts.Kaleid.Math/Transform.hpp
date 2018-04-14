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
		///
		/// Constructor and Destructor
		///
		Transform();
		~Transform();

		///
		/// Translations
		///
		void TranslateRelative(const Vector3F& position);
		void RotateRelative(const Vector3F& rotation);
		void ScaleRelative(const Vector3F& scale);

		void TranslateRelative(const float& x, const float& y, const float& z);
		void RotateRelative(const float& x, const float& y, const float& z);
		void ScaleRelative(const float& x, const float& y, const float& z);

		///
		/// Translational Setters
		///
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

		///
		/// Translational Getters
		///
		const Vector3F& GetRelativePosition() const;
		const Vector3F& GetRelativeRotation() const;
		const Vector3F& GetRelativeScale() const;

		const Vector3F& GetWorldPosition() const;
		const Vector3F& GetWorldRotation() const;
		const Vector3F& GetWorldScale() const;

		Matrix4F& GetModelMatrix();
		const Matrix4F& GetModelMatrix() const;

		///
		/// Directional Getters
		///
		const Matrix4F& GetRelativeOrientation() const;
		const Matrix4F& GetWorldOrientation() const;

		const Vector3F& GetRelativeForward() const;
		const Vector3F& GetRelativeRight() const;
		const Vector3F& GetRelativeUp() const;

		const Vector3F& GetWorldForward() const;
		const Vector3F& GetWorldRight() const;
		const Vector3F& GetWorldUp() const;

		///
		/// Relative Bindings
		///
		Transform const* GetParent() const;

		void AttachParent(Transform* parent);
		void AttachChild(Transform* child);
		void DettachParent(Transform* parent);
		void DettachChild(Transform* child);
	private:
		///
		/// Stored Vectors and Matricies
		///
		Vector3F _r_position;
		Vector3F _r_rotation;
		Vector3F _r_scale;

		mutable Vector3F _w_position;
		mutable Vector3F _w_rotation;
		mutable Vector3F _w_scale;

		Matrix4F _model_matrix;

		mutable Matrix4F _r_orientation;
		mutable Matrix4F _w_orientation;

		mutable Vector3F _r_forward;
		mutable Vector3F _r_right;
		mutable Vector3F _r_up;

		mutable Vector3F _w_forward;
		mutable Vector3F _w_right;
		mutable Vector3F _w_up;

		///
		/// Dirty Tags
		///
		mutable bool _is_position_dirty;
		mutable bool _is_rotation_dirty;
		mutable bool _is_scale_dirty;
		bool _is_model_matrix_dirty;
		mutable bool _is_r_orientaion_dirty;
		mutable bool _is_w_orientaion_dirty;
		mutable bool _is_r_forward_dirty;
		mutable bool _is_r_right_dirty;
		mutable bool _is_r_up_dirty;
		mutable bool _is_w_forward_dirty;
		mutable bool _is_w_right_dirty;
		mutable bool _is_w_up_dirty;

		///
		/// Relative position bindings
		///
		Transform* _parent;
		std::vector<Transform*> _children;

		///
		/// Hidden Methods, important for class operation
		///
		void _MarkPositionDirty();
		void _MarkRotationDirty();
		void _MarkScaleDirty();
	};

	class JAGERTS_KALEID_MATH_API TransformableObject
	{
	public:
		virtual Transform* GetTransform();
		const Transform const* GetTransform() const;
	protected:
		Transform _transform;
	};
}