#pragma once

#include "stdafx.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

API_BEGIN
namespace Kaleid::Math
{
	class KALEID_MATH_API CameraBase abstract
	{
	public:
		CameraBase();

		const Vector3f& GetPosition() const;
		void SetPosition(const Vector3f& position);
		void TranslatePosition(const Vector3f& offset);

		const Vector3f& GetRotation() const;
		void SetRotation(const Vector3f& rotation);
		void TranslateRotation(const Vector3f& offset);

		float GetAspectRatio() const;
		void SetAspectRatio(float aspect_ratio);

		Matrix4f GetOrientation() const;

		Vector3f GetForward() const;
		Vector3f GetRight() const;
		Vector3f GetUp() const;

		virtual Matrix4f GetProjectionMatrix() = 0;
		Matrix4f GetViewMatrix();
	protected:
		void NormalizeRotation();

		Vector3f _position;
		Vector3f _rotation;

		Matrix4f _projection_matrix;
		Matrix4f _view_matrix;

		bool _is_projection_matrix_dirty;
		bool _is_view_matrix_dirty;

		float _aspect_ratio;
	};
}
API_END