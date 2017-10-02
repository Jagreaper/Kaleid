#include "stdafx.hpp"
#include "MouseBinding.hpp"
#include "Window.hpp"

using namespace Kaleid::Input;

MouseBinding::MouseBinding(const MouseCode mouse_code, const MouseBindingState state, const std::function<void(double, double)> action)
{
	this->_mouse_code = mouse_code;
	this->_state = state;
	this->_action = action;
}

void MouseBinding::Poll(Kaleid::Graphics::Window*& window)
{
	char new_glfw_state = window->GetMouseState(this->_mouse_code);
	double new_xpos;
	double new_ypos;
	window->GetMousePosition(&new_xpos, &new_ypos);

	double delta_xpos = new_xpos - this->_old_xpos;
	double delta_ypos = new_ypos - this->_old_ypos;

	if (this->_mouse_code == MouseCode::Moved)
	{
		switch (this->_state)
		{
		case MouseBindingState::MouseMoved:
			if (delta_xpos != 0 || delta_ypos != 0)
				this->_action(new_xpos, new_ypos);
			break;
		default:
			break;
		}
	}
	else if (this->_mouse_code == MouseCode::MovedDelta)
	{
		switch (this->_state)
		{
		case MouseBindingState::MouseMoved:
			if (delta_xpos != 0 || delta_ypos != 0)
				this->_action(delta_xpos, delta_ypos);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (this->_state)
		{
		case MouseBindingState::ButtonPressed:
			if (this->_old_glfw_state == GLFW_RELEASE && new_glfw_state == GLFW_PRESS)
				this->_action(delta_xpos, delta_ypos);
			break;
		case MouseBindingState::ButtonReleased:
			if (this->_old_glfw_state == GLFW_PRESS && new_glfw_state == GLFW_RELEASE)
				this->_action(delta_xpos, delta_ypos);
			break;
		case MouseBindingState::ButtonHeld:
			if (new_glfw_state == GLFW_PRESS)
				this->_action(delta_xpos, delta_ypos);
			break;
		case MouseBindingState::ButtonNotHeld:
			if (new_glfw_state == GLFW_RELEASE)
				this->_action(delta_xpos, delta_ypos);
			break;
		default:
			break;
		}
	}

	this->_old_glfw_state = new_glfw_state;
	this->_old_xpos = new_xpos;
	this->_old_ypos = new_ypos;
}