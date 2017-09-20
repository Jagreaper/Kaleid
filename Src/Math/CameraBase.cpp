#include "stdafx.hpp"
#include "CameraBase.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Kaleid::Math;

CameraBase::CameraBase()
{
	this->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	this->SetRotation(Vector3f(0.0f, 0.0f, 0.0f));
	this->SetAspectRatio(4.0f / 3.0f);
}

const Vector3f& CameraBase::GetPosition() const
{
	return this->_position;
}

void CameraBase::SetPosition(const Vector3f& position)
{
	this->_position = position;
	this->_is_view_matrix_dirty = true;
}

void CameraBase::TranslatePosition(const Vector3f& offset)
{
	this->_position += offset;
	this->_is_view_matrix_dirty = true;
}

const Vector3f& CameraBase::GetRotation() const
{
	return this->_rotation;
}

void CameraBase::SetRotation(const Vector3f& rotation)
{
	this->_rotation = rotation;
	this->NormalizeRotation();
	this->_is_view_matrix_dirty = true;
}

void CameraBase::TranslateRotation(const Vector3f& offset)
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
	assert(aspect_ratio > 0.0);
	this->_aspect_ratio = aspect_ratio;
	this->_is_projection_matrix_dirty = true;
}

Matrix4f CameraBase::GetOrientation() const
{
	Matrix4f orientation;
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.x), Vector3f(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.y), Vector3f(0, 1, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.z), Vector3f(0, 0, 1));
	return orientation;
}

Vector3f CameraBase::GetForward() const
{
	glm::vec4 forward = glm::inverse(this->GetOrientation()) * glm::vec4(0, 0, -1, 1);
	return Vector3f(forward);
}

Vector3f CameraBase::GetRight() const
{
	glm::vec4 right = glm::inverse(this->GetOrientation()) * glm::vec4(1, 0, 0, 1);
	return Vector3f(right);
}

Vector3f CameraBase::GetUp() const
{
	glm::vec4 up = glm::inverse(this->GetOrientation()) * glm::vec4(0, 1, 0, 1);
	return Vector3f(up);
}

Matrix4f CameraBase::GetViewMatrix()
{
	if (this->_is_view_matrix_dirty)
	{
		this->_view_matrix = this->GetOrientation() * glm::translate(Matrix4f(), -this->_position);
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