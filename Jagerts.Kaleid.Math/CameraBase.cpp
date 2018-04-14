#include "CameraBase.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <cmath>

using namespace Jagerts::Kaleid::Math;

CameraBase::CameraBase()
{
	this->_transform.SetRelativePosition(Vector3F(0.0f, 0.0f, 0.0f));
	this->_transform.SetRelativeRotation(Vector3F(0.0f, 0.0f, 0.0f));
	this->SetAspectRatio(4.0f / 3.0f);
}

Transform* CameraBase::GetTransform()
{
	this->_is_view_matrix_dirty = true;
	return TransformableObject::GetTransform();
}

float CameraBase::GetAspectRatio() const
{
	return this->_aspect_ratio;
}

void CameraBase::SetAspectRatio(float aspect_ratio)
{
	if (aspect_ratio <= 0.0)
		return;

	this->_aspect_ratio = aspect_ratio;
	this->_is_projection_matrix_dirty = true;
}

Matrix4F CameraBase::GetViewMatrix()
{
	if (this->_is_view_matrix_dirty)
	{
		this->_NormalizeRotation();
		this->_view_matrix = this->_transform.GetWorldOrientation() * glm::translate(Matrix4F(), -this->_transform.GetWorldPosition());
		this->_is_view_matrix_dirty = false;
	}

	return this->_view_matrix;
}

void _NormalizeRotationalAxis(float& axis)
{
	axis = fmodf(axis, 360.0f);
	if (isnan(axis))
		axis = 0.0f;
	if (axis < 0.0f)
		axis += 360.0f;
}

void CameraBase::_NormalizeRotation()
{
	Vector3F rotation = this->_transform.GetWorldRotation();
	_NormalizeRotationalAxis(rotation.x);
	_NormalizeRotationalAxis(rotation.y);
	_NormalizeRotationalAxis(rotation.z);
	this->_transform.SetWorldRotation(rotation);
}