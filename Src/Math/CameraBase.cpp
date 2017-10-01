#include "stdafx.hpp"
#include "CameraBase.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Kaleid::Math;

CameraBase::CameraBase()
{
	this->SetPosition(Vector3F(0.0f, 0.0f, 0.0f));
	this->SetRotation(Vector3F(0.0f, 0.0f, 0.0f));
	this->SetAspectRatio(4.0f / 3.0f);
}

const Vector3F& CameraBase::GetPosition() const
{
	return this->_position;
}

void CameraBase::SetPosition(const Vector3F& position)
{
	this->_position = position;
	this->_is_view_matrix_dirty = true;
}

void CameraBase::TranslatePosition(const Vector3F& offset)
{
	this->_position += offset;
	this->_is_view_matrix_dirty = true;
}

const Vector3F& CameraBase::GetRotation() const
{
	return this->_rotation;
}

void CameraBase::SetRotation(const Vector3F& rotation)
{
	this->_rotation = rotation;
	this->NormalizeRotation();
	this->_is_view_matrix_dirty = true;
}

void CameraBase::TranslateRotation(const Vector3F& offset)
{
	this->_rotation += offset;
	this->NormalizeRotation();
	this->_is_view_matrix_dirty = true;
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

Matrix4F CameraBase::GetOrientation() const
{
	Matrix4F orientation;
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.x), Vector3F(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.y), Vector3F(0, 1, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.z), Vector3F(0, 0, 1));
	return orientation;
}

Vector3F CameraBase::GetForward() const
{
	glm::vec4 forward = glm::inverse(this->GetOrientation()) * glm::vec4(0, 0, -1, 1);
	return Vector3F(forward);
}

Vector3F CameraBase::GetRight() const
{
	glm::vec4 right = glm::inverse(this->GetOrientation()) * glm::vec4(1, 0, 0, 1);
	return Vector3F(right);
}

Vector3F CameraBase::GetUp() const
{
	glm::vec4 up = glm::inverse(this->GetOrientation()) * glm::vec4(0, 1, 0, 1);
	return Vector3F(up);
}

Matrix4F CameraBase::GetViewMatrix()
{
	if (this->_is_view_matrix_dirty)
	{
		this->_view_matrix = this->GetOrientation() * glm::translate(Matrix4F(), -this->_position);
		this->_is_view_matrix_dirty = false;
	}

	return this->_view_matrix;
}

void CameraBase::NormalizeRotation()
{
	this->_rotation.x = fmodf(this->_rotation.x, 360.0f);
	if (this->_rotation.x < 0.0f)
		this->_rotation.x += 360.0f;

	this->_rotation.y = fmodf(this->_rotation.y, 360.0f);
	if (this->_rotation.y < 0.0f)
		this->_rotation.y += 360.0f;

	this->_rotation.z = fmodf(this->_rotation.z, 360.0f);
	if (this->_rotation.z < 0.0f)
		this->_rotation.z += 360.0f;
}