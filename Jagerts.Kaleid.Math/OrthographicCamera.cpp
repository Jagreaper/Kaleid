#include "OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace Jagerts::Kaleid::Math;

OrthographicCamera::OrthographicCamera()
	: CameraBase::CameraBase()
{
	this->SetLeft(-1.0f);
	this->SetRight(1.0f);
	this->SetTop(1.0f);
	this->SetBottom(-1.0f);
}

Matrix4F OrthographicCamera::GetProjectionMatrix()
{
	if (this->_is_projection_matrix_dirty)
	{
		this->_projection_matrix = glm::ortho(this->_left, this->_right, this->_bottom, this->_top);
		this->_is_projection_matrix_dirty = false;
	}

	return this->_projection_matrix;
}

bool OrthographicCamera::IsPerspective()
{
	return false;
}

bool OrthographicCamera::IsOrthographic()
{
	return true;
}

jkGetterSetterSourceDefinition(OrthographicCamera, Left, const float, this->_left)
jkGetterSetterSourceDefinition(OrthographicCamera, Right, const float, this->_right)
jkGetterSetterSourceDefinition(OrthographicCamera, Top, const float, this->_top)
jkGetterSetterSourceDefinition(OrthographicCamera, Bottom, const float, this->_bottom)