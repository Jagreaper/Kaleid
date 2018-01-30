#include "Mouse.hpp"
#include "MouseClickBinding.hpp"
#include "Jagerts.Kaleid.Graphics/Window.hpp"

using namespace Jagerts::Kaleid::Input;

MouseClickBinding::MouseClickBinding(const MouseClickCode mouse_code, const MouseClickBindingState state, const std::function<void()> action)
{
	this->_mouse_code = mouse_code;
	this->_state = state;
	this->_action = action;
}

void MouseClickBinding::Poll(Jagerts::Kaleid::Graphics::Window*& window, Mouse* mouse)
{
	char new_glfw_state = window->GetMouseState(this->_mouse_code);

	switch (this->_state)
	{
	case MouseClickBindingState::ButtonPressed:
		if (this->_old_glfw_state == GLFW_RELEASE && new_glfw_state == GLFW_PRESS)
			this->_action();
		break;
	case MouseClickBindingState::ButtonReleased:
		if (this->_old_glfw_state == GLFW_PRESS && new_glfw_state == GLFW_RELEASE)
			this->_action();
		break;
	case MouseClickBindingState::ButtonHeld:
		if (new_glfw_state == GLFW_PRESS)
			this->_action();
		break;
	case MouseClickBindingState::ButtonNotHeld:
		if (new_glfw_state == GLFW_RELEASE)
			this->_action();
		break;
	default:
		break;
	}

	this->_old_glfw_state = new_glfw_state;
}