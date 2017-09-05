#include "stdafx.hpp"
#include "PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Kaleid::Math;

PerspectiveCamera::PerspectiveCamera()
{
	this->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	this->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->SetFov(50.0f);
	this->SetNearZ(0.01f);
	this->SetFarZ(100.0f);
	this->SetAspectRatio(4.0f / 3.0f);
}

const glm::vec3& PerspectiveCamera::GetPosition() const
{
	return this->_position;
}

void PerspectiveCamera::SetPosition(const glm::vec3& position)
{
	this->_position = position;
	this->_is_view_matrix_dirty = true;
}

void PerspectiveCamera::TranslatePosition(const glm::vec3& offset)
{
	this->_position += offset;
	this->_is_view_matrix_dirty = true;
}

const glm::vec3& PerspectiveCamera::GetRotation() const
{
	return this->_rotation;
}

void PerspectiveCamera::SetRotation(const glm::vec3& rotation)
{
	this->_rotation = rotation;
	this->NormalizeRotation();
	this->_is_view_matrix_dirty = true;
}

void PerspectiveCamera::TranslateRotation(const glm::vec3& offset)
{
	this->_rotation += offset;
	this->NormalizeRotation();
	this->_is_view_matrix_dirty = true;
}

float PerspectiveCamera::GetFov() const
{
	return this->_fov;
}

void PerspectiveCamera::SetFov(float fov)
{
	assert(fov > 0.0f && fov < 180.0f);
	this->_fov = fov;
	this->_is_projection_matrix_dirty = true;
}

float PerspectiveCamera::GetNearZ() const
{
	return this->_z_near;
}

void PerspectiveCamera::SetNearZ(float z_near)
{
	assert(z_near > 0.0f);
	this->_z_near = z_near;
	this->_is_projection_matrix_dirty = true;
}

float PerspectiveCamera::GetFarZ() const
{
	return this->_z_far;
}

void PerspectiveCamera::SetFarZ(float z_far)
{
	assert(z_far > this->_z_near);
	this->_z_far = z_far;
	this->_is_projection_matrix_dirty = true;
}

float PerspectiveCamera::GetAspectRatio() const
{
	return this->_aspect_ratio;
}

void PerspectiveCamera::SetAspectRatio(float aspect_ratio)
{
	assert(aspect_ratio > 0.0);
	this->_aspect_ratio = aspect_ratio;
	this->_is_projection_matrix_dirty = true;
}

glm::mat4 PerspectiveCamera::GetOrientation() const
{
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.x), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.y), glm::vec3(0, 1, 0));
	orientation = glm::rotate(orientation, glm::radians(this->_rotation.z), glm::vec3(0, 0, 1));
	return orientation;
}

glm::vec3 PerspectiveCamera::GetForward() const
{
	glm::vec4 forward = glm::inverse(this->GetOrientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 PerspectiveCamera::GetRight() const
{
	glm::vec4 right = glm::inverse(this->GetOrientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 PerspectiveCamera::GetUp() const
{
	glm::vec4 up = glm::inverse(this->GetOrientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}

glm::mat4 PerspectiveCamera::GetProjectionMatrix()
{
	if (this->_is_projection_matrix_dirty)
	{
		this->_projection_matrix = glm::perspective(glm::radians(this->_fov), this->_aspect_ratio, this->_z_near, this->_z_far);
		this->_is_projection_matrix_dirty = false;
	}

	return this->_projection_matrix;
}

glm::mat4 PerspectiveCamera::GetViewMatrix()
{
	if (this->_is_view_matrix_dirty)
	{
		this->_view_matrix = this->GetOrientation() * glm::translate(glm::mat4(), -this->_position);
		this->_is_view_matrix_dirty = false;
	}

	return this->_view_matrix;
}

void PerspectiveCamera::NormalizeRotation()
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