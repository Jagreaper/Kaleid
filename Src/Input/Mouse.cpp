#include "stdafx.hpp"
#include "Mouse.hpp"
#include "VectorHelper.hpp"
#include "Window.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;
using namespace Kaleid::Input;

Mouse::Mouse()
{
	this->_old_xpos = 0.0;
	this->_old_ypos = 0.0;
}

Mouse::Mouse(const std::vector<MouseBinding>& mouse_bindings)
{
	this->Add(mouse_bindings);
}

Mouse::Mouse(const std::vector<MouseBinding>* mouse_bindings)
{
	this->Add(mouse_bindings);
}

void Mouse::Add(MouseBinding& mouse_binding)
{
	this->_mouse_bindings.push_back(mouse_binding);
}

void Mouse::Add(const std::vector<MouseBinding>& mouse_bindings)
{
	VectorHelper::AddRange(this->_mouse_bindings, mouse_bindings);
}

void Mouse::Add(const std::vector<MouseBinding>* mouse_bindings)
{
	VectorHelper::AddRange(this->_mouse_bindings, mouse_bindings);
}

void Mouse::Remove(const unsigned int index)
{
	this->_mouse_bindings.erase(this->_mouse_bindings.begin() + index);
}

void Mouse::Poll(Kaleid::Graphics::Window*& window)
{
	window->GetMousePosition(&this->_xpos, &this->_ypos);

	this->_delta_xpos = this->_xpos - this->_old_xpos;
	this->_delta_ypos = this->_ypos - this->_old_ypos;

	for (unsigned int index = 0; index < this->_mouse_bindings.size(); index++)
		this->_mouse_bindings[index].Poll(window, this);

	this->_old_xpos = this->_xpos;
	this->_old_ypos = this->_ypos;
}

void Mouse::Clear()
{
	this->_mouse_bindings.clear();
}

void Mouse::GetPosition(double* xpos, double* ypos)
{
	*xpos = this->_xpos;
	*ypos = this->_ypos;
}

void Mouse::GetDeltaPosition(double* xpos, double* ypos)
{
	*xpos = this->_delta_xpos;
	*ypos = this->_delta_ypos;
}

const double& Mouse::GetPositionX() const
{
	return this->_xpos;
}

const double& Mouse::GetPositionY() const
{
	return this->_ypos;
}

const double& Mouse::GetDeltaPositionX() const
{
	return this->_delta_xpos;
}

const double& Mouse::GetDeltaPositionY() const
{
	return this->_delta_ypos;
}