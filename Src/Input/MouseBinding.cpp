#include "stdafx.hpp"
#include "Mouse.hpp"
#include "MouseBinding.hpp"
#include "Window.hpp"

using namespace Kaleid::Input;

MouseBinding::MouseBinding(const MouseCode mouse_code, const MouseBindingState state, const std::function<void(double, double)> action)
{
	this->_mouse_code = mouse_code;
	this->_state = state;
	this->_action = action;
}

void MouseBinding::Poll(Kaleid::Graphics::Window*& window, Mouse* mouse)
{
	char new_glfw_state = window->GetMouseState(this->_mouse_code);

	switch (this->_state)
	{
	case MouseBindingState::MouseMoved:
		if (this->_mouse_code == MouseCode::Moved && mouse->_delta_xpos != 0 || mouse->_delta_ypos != 0)
			this->_action(mouse->_xpos, mouse->_ypos);
		else if (this->_mouse_code == MouseCode::MovedDelta && mouse->_delta_xpos != 0 || mouse->_delta_ypos != 0)
			this->_action(mouse->_delta_xpos, mouse->_delta_ypos);
		break;
	case MouseBindingState::ButtonPressed:
		if (this->_old_glfw_state == GLFW_RELEASE && new_glfw_state == GLFW_PRESS)
			this->_action(mouse->_delta_xpos, mouse->_delta_ypos);
		break;
	case MouseBindingState::ButtonReleased:
		if (this->_old_glfw_state == GLFW_PRESS && new_glfw_state == GLFW_RELEASE)
			this->_action(mouse->_delta_xpos, mouse->_delta_ypos);
		break;
	case MouseBindingState::ButtonHeld:
		if (new_glfw_state == GLFW_PRESS)
			this->_action(mouse->_delta_xpos, mouse->_delta_ypos);
		break;
	case MouseBindingState::ButtonNotHeld:
		if (new_glfw_state == GLFW_RELEASE)
			this->_action(mouse->_delta_xpos, mouse->_delta_ypos);
		break;
	default:
		break;
	}

	this->_old_glfw_state = new_glfw_state;
}