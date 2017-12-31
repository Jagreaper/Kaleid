#include "stdafx.hpp"
#include "Mouse.hpp"
#include "MouseMoveBinding.hpp"
#include "Window.hpp"

using namespace Kaleid::Input;

MouseMoveBinding::MouseMoveBinding(const MouseMoveType _type, const MouseMoveBindingState state, const std::function<void(double, double)> action)
{
	this->_state = state;
	this->_action = action;
}

void MouseMoveBinding::Poll(Kaleid::Graphics::Window*& window, Mouse* mouse)
{
	double x = this->_type == MouseMoveType::Normal ? mouse->_xpos : mouse->_delta_xpos;
	double y = this->_type == MouseMoveType::Normal ? mouse->_ypos : mouse->_delta_ypos;

	switch (this->_state)
	{
	case MouseMoveBindingState::Centered:
		this->_action(x, y);
		break;
	case MouseMoveBindingState::Normal:
		this->_action(x, y);
		break;
	default:
		break;
	}
}