#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Vector.hpp"
#include "Jagerts.Kaleid.Math/Matrix.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"

namespace Jagerts::Kaleid::Math
{
	class JAGERTS_KALEID_MATH_API CameraBase : public TransformableObject
	{
	public:
		CameraBase();

		Transform* GetTransform();
		using TransformableObject::GetTransform;

		float GetAspectRatio() const;
		void SetAspectRatio(float aspect_ratio);

		virtual Matrix4F GetProjectionMatrix() = 0;
		Matrix4F GetViewMatrix();
		virtual bool IsPerspective() = 0;
		virtual bool IsOrthographic() = 0;
	protected:
		void _NormalizeRotation();

		Matrix4F _projection_matrix;
		Matrix4F _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _aspect_ratio;
	};
}