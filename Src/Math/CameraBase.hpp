#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

namespace Kaleid::Math
{
	class KALEID_MATH_API CameraBase
	{
	public:
		CameraBase();

		const Vector3F& GetPosition() const;
		void SetPosition(const Vector3F& position);
		void TranslatePosition(const Vector3F& offset);

		const Vector3F& GetRotation() const;
		void SetRotation(const Vector3F& rotation);
		void TranslateRotation(const Vector3F& offset);

		float GetAspectRatio() const;
		void SetAspectRatio(float aspect_ratio);

		Matrix4F GetOrientation() const;

		Vector3F GetForward() const;
		Vector3F GetRight() const;
		Vector3F GetUp() const;

		virtual Matrix4F GetProjectionMatrix() = 0;
		Matrix4F GetViewMatrix();
		virtual bool IsPerspective() = 0;
		virtual bool IsOrthographic() = 0;
	protected:
		void NormalizeRotation();

		Vector3F _position;
		Vector3F _rotation;

		Matrix4F _projection_matrix;
		Matrix4F _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _aspect_ratio;
	};
}