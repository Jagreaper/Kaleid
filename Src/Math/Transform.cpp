#include "stdafx.hpp"
#include "Transform.hpp"
#include "GLM\gtx\rotate_vector.hpp"
#include "GLM\gtc\matrix_transform.hpp"

using namespace Kaleid::Math;

Transform::Transform()
{
	this->_r_position = Vector3f(0.0f, 0.0f, 0.0f);
	this->_r_rotation = Vector3f(0.0f, 0.0f, 0.0f);
	this->_r_scale = Vector3f(1.0f, 1.0f, 1.0f);

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

	for (int index = 0; index < this->_children.size(); index++)
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

	for (int index = 0; index < this->_children.size(); index++)
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

	for (int index = 0; index < this->_children.size(); index++)
	{
		this->_children[index]->_is_scale_dirty = true;
		this->_children[index]->_is_model_matrix_dirty = true;
		this->_children[index]->MarkScaleDirty();
	}
}

void Transform::TranslateRelative(Vector3f& position)
{
	this->_r_position += position;
	this->MarkPositionDirty();
}

void Transform::RotateRelative(Vector3f& rotation)
{
	this->_r_rotation += rotation;
	this->MarkRotationDirty();
}

void Transform::ScaleRelative(Vector3f& scale)
{
	this->_r_scale *= scale;
	this->MarkScaleDirty();
}

void Transform::SetRelativePosition(Vector3f& position)
{
	this->_r_position = position;
	this->MarkPositionDirty();
}

void Transform::SetRelativeRotation(Vector3f& rotation)
{
	this->_r_rotation = rotation;
	this->MarkRotationDirty();
}

void Transform::SetRelativeScale(Vector3f& scale)
{
	this->_r_scale = scale;
	this->MarkScaleDirty();
}

Vector3f RotateRelativeByWorld(Vector3f& p_rotation, Vector3f& r_postion)
{
	glm::vec2 xy = glm::rotate(glm::vec2(r_postion.x, r_postion.y), glm::radians(p_rotation.z));
	glm::vec2 zy = glm::rotate(glm::vec2(r_postion.z, r_postion.y), glm::radians(p_rotation.x));
	glm::vec2 xz = glm::rotate(glm::vec2(r_postion.x, r_postion.z), glm::radians(p_rotation.y));

	float x = xy.x + xz.x;
	float y = xy.y + zy.y;
	float z = zy.x + xz.y;

	return Vector3f(x, y, z);
}

void Transform::SetWorldPosition(Vector3f& position)
{
	if (this->_parent != NULL)
		this->SetRelativePosition(position - RotateRelativeByWorld(-this->_parent->GetWorldRotation(), this->_parent->GetWorldPosition()));
	else
		this->SetRelativePosition(position);

	this->MarkPositionDirty();
}

void Transform::SetWorldRotation(Vector3f& rotation)
{
	if (this->_parent != NULL)
		this->SetRelativeRotation(rotation - this->_parent->GetWorldRotation());
	else
		this->SetRelativeRotation(rotation);

	this->MarkRotationDirty();
}

void Transform::SetWorldScale(Vector3f& scale)
{
	if (this->_parent != NULL)
		this->SetRelativeScale(scale / this->_parent->GetWorldScale());
	else
		this->SetRelativeScale(scale);

	this->MarkScaleDirty();
}

Vector3f Transform::GetRelativePosition()
{
	return this->_r_position;
}

Vector3f Transform::GetRelativeRotation()
{
	return this->_r_rotation;
}

Vector3f Transform::GetRelativeScale()
{
	return this->_r_scale;
}

Vector3f Transform::GetWorldPosition()
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

Vector3f Transform::GetWorldRotation()
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

Vector3f Transform::GetWorldScale()
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

Transform* Transform::GetParent()
{
	return this->_parent;
}


Matrix4f Transform::GetModelMatrix()
{
	if (this->_is_model_matrix_dirty)
	{
		Vector3f w_position = this->GetWorldPosition();
		Vector3f w_rotation = this->GetWorldRotation();
		Vector3f w_scale = this->GetWorldScale();
		Matrix4f translation = glm::translate(Matrix4f(), w_position);
		Matrix4f rot_x = glm::rotate(glm::radians(w_rotation.x), Vector3f(1.0f, 0.0f, 0.0f));
		Matrix4f rot_y = glm::rotate(glm::radians(w_rotation.y), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4f rot_z = glm::rotate(glm::radians(w_rotation.z), Vector3f(0.0f, 0.0f, 1.0f));
		Matrix4f scale = glm::scale(w_scale);
		Matrix4f rot = rot_x * rot_y * rot_z;
		this->_model_matrix = translation * rot * scale;
		this->_is_model_matrix_dirty = false;
	}

	return this->_model_matrix;
}

void Transform::AttachParent(Transform*& parent)
{
	if (parent != NULL)
	{
		this->_parent = parent;
		parent->_children.push_back(this);
	}
}

void Transform::AttachChild(Transform*& child)
{
	if (child != NULL)
	{
		child->_parent = this;
		this->_children.push_back(child);
	}
}

void Transform::DettachParent(Transform*& parent)
{
	if (parent != NULL)
	{
		for (int index = 0; index < parent->_children.size(); index++)
		{
			if (parent->_children[index] == this)
				parent->_children.erase(parent->_children.begin() + index);

			this->_parent = NULL;
		}
	}
}

void Transform::DettachChild(Transform*& child)
{
	if (child != NULL)
	{
		for (int index = 0; index < this->_children.size(); index++)
		{
			if (this->_children[index] == child)
				this->_children.erase(this->_children.begin() + index);

			child->_parent = NULL;
		}
	}
}