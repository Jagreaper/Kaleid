#include "stdafx.hpp"
#include "KeyBinding.hpp"
#include "Window.hpp"

using namespace Kaleid::Input;

KeyBinding::KeyBinding(const KeyCode key_code, const KeyBindingState state, const std::function<void()> action)
{
	this->_key_code = key_code;
	this->_state = state;
	this->_action = action;
}

void KeyBinding::Poll(Kaleid::Graphics::Window*& window)
{
	char new_glfw_state = window->GetKeyState(this->_key_code);
	switch (this->_state)
	{
	case KeyBindingState::Pressed:
		if (this->_old_glfw_state == GLFW_RELEASE && new_glfw_state == GLFW_PRESS)
			this->_action();
		break;
	case KeyBindingState::Released:
		if (this->_old_glfw_state == GLFW_PRESS && new_glfw_state == GLFW_RELEASE)
			this->_action();
		break;
	case KeyBindingState::Held:
		if (new_glfw_state == GLFW_PRESS)
			this->_action();
		break;
	case KeyBindingState::NotHeld:
		if (new_glfw_state == GLFW_RELEASE)
			this->_action();
		break;
	default:
		break;
	}

	this->_old_glfw_state = new_glfw_state;
}