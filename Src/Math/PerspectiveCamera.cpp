#include "stdafx.hpp"
#include "PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Kaleid::Math;

PerspectiveCamera::PerspectiveCamera()
	: CameraBase::CameraBase()
{
	this->SetFov(50.0f);
	this->SetNearZ(0.01f);
	this->SetFarZ(100.0f);
}

float PerspectiveCamera::GetFov() const
{
	return this->_fov;
}

void PerspectiveCamera::SetFov(float fov)
{
	if (fov <= 0.0f || fov >= 180.0f)
		return;

	this->_fov = fov;

	this->_is_projection_matrix_dirty = true;
}

float PerspectiveCamera::GetNearZ() const
{
	return this->_z_near;
}

void PerspectiveCamera::SetNearZ(float z_near)
{
	if (z_near <= 0.0f)
		return;

	this->_z_near = z_near;
	this->_is_projection_matrix_dirty = true;
}

float PerspectiveCamera::GetFarZ() const
{
	return this->_z_far;
}

void PerspectiveCamera::SetFarZ(float z_far)
{
	if (z_far <= this->_z_near)
		return;

	this->_z_far = z_far;
	this->_is_projection_matrix_dirty = true;
}

Matrix4F PerspectiveCamera::GetProjectionMatrix()
{
	if (this->_is_projection_matrix_dirty)
	{
		this->_projection_matrix = glm::perspective(glm::radians(this->_fov), this->_aspect_ratio, this->_z_near, this->_z_far);
		this->_is_projection_matrix_dirty = false;
	}

	return this->_projection_matrix;
}