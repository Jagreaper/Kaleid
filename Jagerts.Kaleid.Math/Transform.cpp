#include "Transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtc/matrix_transform.hpp"

using namespace Jagerts::Kaleid::Math;

Transform::Transform()
{
	this->_r_position = Vector3F(0.0f, 0.0f, 0.0f);
	this->_r_rotation = Vector3F(0.0f, 0.0f, 0.0f);
	this->_r_scale = Vector3F(1.0f, 1.0f, 1.0f);

	this->_is_position_dirty = true;
	this->_is_rotation_dirty = true;
	this->_is_scale_dirty = true;
	this->_is_model_matrix_dirty = true;

	this->_parent = NULL;
}

Transform::~Transform()
{
	// Skip
}

void Transform::MarkPositionDirty()
{
	this->_is_position_dirty = true;
	this->_is_model_matrix_dirty = true;

	for (unsigned int index = 0; index < (unsigned int)this->_children.size(); index++)
	{
		this->_children[index]->_is_position_dirty = true;
		this->_children[index]->_is_model_matrix_dirty = true;
		this->_children[index]->MarkPositionDirty();
	}
}

void Transform::MarkRotationDirty()
{
	this->_is_rotation_dirty = true;
	this->_is_model_matrix_dirty = true;

	for (unsigned int index = 0; index < (unsigned int)this->_children.size(); index++)
	{
		this->_children[index]->_is_rotation_dirty = true;
		this->_children[index]->_is_model_matrix_dirty = true;
		this->_children[index]->MarkRotationDirty();
	}
}

void Transform::MarkScaleDirty()
{
	this->_is_scale_dirty = true;
	this->_is_model_matrix_dirty = true;

	for (unsigned int index = 0; index < (unsigned int)this->_children.size(); index++)
	{
		this->_children[index]->_is_scale_dirty = true;
		this->_children[index]->_is_model_matrix_dirty = true;
		this->_children[index]->MarkScaleDirty();
	}
}

void Transform::TranslateRelative(const Vector3F& position)
{
	this->_r_position += position;
	this->MarkPositionDirty();
}

void Transform::RotateRelative(const Vector3F& rotation)
{
	this->_r_rotation += rotation;
	this->MarkRotationDirty();
}

void Transform::ScaleRelative(const Vector3F& scale)
{
	this->_r_scale *= scale;
	this->MarkScaleDirty();
}

void Transform::TranslateRelative(const float& x, const float& y, const float& z)
{
	this->_r_position.x += x;
	this->_r_position.y += y;
	this->_r_position.z += z;
	this->MarkPositionDirty();
}

void Transform::RotateRelative(const float& x, const float& y, const float& z)
{
	this->_r_rotation.x += x;
	this->_r_rotation.y += y;
	this->_r_rotation.z += z;
	this->MarkRotationDirty();
}

void Transform::ScaleRelative(const float& x, const float& y, const float& z)
{
	this->_r_scale.x *= x;
	this->_r_scale.y *= y;
	this->_r_scale.z *= z;
	this->MarkScaleDirty();
}

void Transform::SetRelativePosition(const Vector3F& position)
{
	this->_r_position = position;
	this->MarkPositionDirty();
}

void Transform::SetRelativeRotation(const Vector3F& rotation)
{
	this->_r_rotation = rotation;
	this->MarkRotationDirty();
}

void Transform::SetRelativeScale(const Vector3F& scale)
{
	this->_r_scale = scale;
	this->MarkScaleDirty();
}

Vector3F Transform::RotateRelativeByWorld(const Vector3F& p_rotation, const Vector3F& r_postion)
{
	glm::vec2 xy = glm::rotate(glm::vec2(r_postion.x, r_postion.y), glm::radians(p_rotation.z));
	glm::vec2 zy = glm::rotate(glm::vec2(r_postion.z, r_postion.y), glm::radians(p_rotation.x));
	glm::vec2 xz = glm::rotate(glm::vec2(r_postion.x, r_postion.z), glm::radians(p_rotation.y));

	float x = xy.x + xz.x;
	float y = xy.y + zy.y;
	float z = zy.x + xz.y;

	return Vector3F(x, y, z);
}

void Transform::SetWorldPosition(const Vector3F& position)
{
	if (this->_parent != NULL)
		this->SetRelativePosition(position - RotateRelativeByWorld(-this->_parent->GetWorldRotation(), this->_parent->GetWorldPosition()));
	else
		this->SetRelativePosition(position);
}

void Transform::SetWorldRotation(const Vector3F& rotation)
{
	if (this->_parent != NULL)
		this->SetRelativeRotation(rotation - this->_parent->GetWorldRotation());
	else
		this->SetRelativeRotation(rotation);
}

void Transform::SetWorldScale(const Vector3F& scale)
{
	if (this->_parent != NULL)
		this->SetRelativeScale(scale / this->_parent->GetWorldScale());
	else
		this->SetRelativeScale(scale);
}

void Transform::SetRelativePosition(const float& x, const float& y, const float& z)
{
	this->_r_position.x = x;
	this->_r_position.y = y;
	this->_r_position.z = z;
	this->MarkPositionDirty();
}

void Transform::SetRelativeRotation(const float& x, const float& y, const float& z)
{
	this->_r_rotation.x = x;
	this->_r_rotation.y = y;
	this->_r_rotation.z = z;
	this->MarkRotationDirty();
}

void Transform::SetRelativeScale(const float& x, const float& y, const float& z)
{
	this->_r_scale.x = x;
	this->_r_scale.y = y;
	this->_r_scale.z = z;
	this->MarkScaleDirty();
}

void Transform::SetWorldPosition(const float& x, const float& y, const float& z)
{
	Vector3F offset = RotateRelativeByWorld(-this->_parent->GetWorldRotation(), this->_parent->GetWorldPosition());

	if (this->_parent != NULL)
		this->SetRelativePosition(x - offset.x, y - offset.y, z - offset.z);
	else
		this->SetRelativePosition(x, y, z);
}

void Transform::SetWorldRotation(const float& x, const float& y, const float& z)
{
	Vector3F offset = this->_parent->GetWorldRotation();

	if (this->_parent != NULL)
		this->SetRelativeRotation(x - offset.x, y - offset.y, z - offset.z);
	else
		this->SetRelativeRotation(x, y, z);
}

void Transform::SetWorldScale(const float& x, const float& y, const float& z)
{
	Vector3F offset = this->_parent->GetWorldScale();

	if (this->_parent != NULL)
		this->SetRelativeScale(x - offset.x, y - offset.y, z - offset.z);
	else
		this->SetRelativeScale(x, y, z);
}

Vector3F& Transform::GetRelativePosition()
{
	return this->_r_position;
}

Vector3F& Transform::GetRelativeRotation()
{
	return this->_r_rotation;
}

Vector3F& Transform::GetRelativeScale()
{
	return this->_r_scale;
}

Vector3F& Transform::GetWorldPosition()
{
	if (this->_is_position_dirty)
	{
		if (this->_parent != NULL)
			this->_w_position = this->_parent->GetWorldPosition() + RotateRelativeByWorld(this->_parent->GetWorldRotation(), this->GetRelativePosition());
		else
			this->_w_position = this->GetRelativePosition();

		this->_is_position_dirty = false;
	}

	return this->_w_position;
}

Vector3F& Transform::GetWorldRotation()
{
	if (this->_is_rotation_dirty)
	{
		if (this->_parent != NULL)
			this->_w_rotation = this->_parent->GetWorldRotation() + this->GetRelativeRotation();
		else
			this->_w_rotation = this->GetRelativeRotation();

		this->_is_rotation_dirty = false;
	}

	return this->_w_rotation;
}

Vector3F& Transform::GetWorldScale()
{
	if (this->_is_scale_dirty)
	{
		if (this->_parent != NULL)
			this->_w_scale = this->_parent->GetWorldScale() * this->GetRelativeScale();
		else
			this->_w_scale = this->GetRelativeScale();

		this->_is_scale_dirty = false;
	}

	return this->_w_scale;
}

const Vector3F& Transform::GetRelativePosition() const
{
	return this->GetRelativePosition();
}

const Vector3F& Transform::GetRelativeRotation() const
{
	return this->GetRelativeRotation();
}

const Vector3F& Transform::GetRelativeScale() const
{
	return this->GetRelativeScale();
}

const Vector3F& Transform::GetWorldPosition() const
{
	return this->GetWorldPosition();
}

const Vector3F& Transform::GetWorldRotation() const
{
	return this->GetWorldRotation();
}

const Vector3F& Transform::GetWorldScale() const
{
	return this->GetWorldScale();
}

Transform const* Transform::GetParent() const
{
	return this->_parent;
}

Matrix4F& Transform::GetModelMatrix()
{
	if (this->_is_model_matrix_dirty)
	{
		Vector3F w_position = this->GetWorldPosition();
		Vector3F w_rotation = this->GetWorldRotation();
		Vector3F w_scale = this->GetWorldScale();
		Matrix4F translation = glm::translate(Matrix4F(), w_position);
		Matrix4F rot_x = glm::rotate(glm::radians(w_rotation.x), Vector3F(1.0f, 0.0f, 0.0f));
		Matrix4F rot_y = glm::rotate(glm::radians(w_rotation.y), Vector3F(0.0f, 1.0f, 0.0f));
		Matrix4F rot_z = glm::rotate(glm::radians(w_rotation.z), Vector3F(0.0f, 0.0f, 1.0f));
		Matrix4F scale = glm::scale(w_scale);
		Matrix4F rot = rot_x * rot_y * rot_z;
		this->_model_matrix = translation * rot * scale;
		this->_is_model_matrix_dirty = false;
	}

	return this->_model_matrix;
}

const Matrix4F& Transform::GetModelMatrix() const
{
	return this->GetModelMatrix();
}

void Transform::AttachParent(Transform* parent)
{
	if (parent != NULL)
	{
		this->_parent = parent;
		parent->_children.push_back(this);
	}
}

void Transform::AttachChild(Transform* child)
{
	if (child != NULL)
	{
		child->_parent = this;
		this->_children.push_back(child);
	}
}

void Transform::DettachParent(Transform* parent)
{
	if (parent != NULL)
	{
		for (unsigned int index = 0; index < (unsigned int)parent->_children.size(); index++)
		{
			if (parent->_children[index] == this)
				parent->_children.erase(parent->_children.begin() + index);

			this->_parent = NULL;
		}
	}
}

void Transform::DettachChild(Transform* child)
{
	if (child != NULL)
	{
		for (unsigned int index = 0; index < (unsigned int)this->_children.size(); index++)
		{
			if (this->_children[index] == child)
				this->_children.erase(this->_children.begin() + index);

			child->_parent = NULL;
		}
	}
}

Jagerts::Kaleid::Math::Transform* TransformableObject::GetTransform()
{
	return &this->_transform;
}