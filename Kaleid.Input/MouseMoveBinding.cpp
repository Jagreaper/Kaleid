#include "Mouse.hpp"
#include "MouseMoveBinding.hpp"
#include "Kaleid.Graphics\Window.hpp"

using namespace Kaleid::Input;

MouseMoveBinding::MouseMoveBinding(const MouseMoveType type, const std::function<void(double, double)> action)
{
	this->_type = type;
	this->_action = action;
}

void MouseMoveBinding::Poll(Kaleid::Graphics::Window*& window, Mouse* mouse)
{
	double x, y;
	switch (this->_type)
	{
	case MouseMoveType::Normal:
		x = mouse->_xpos;
		y = mouse->_ypos;
		break;
	case MouseMoveType::Delta:
		x = mouse->_delta_xpos;
		y = mouse->_delta_ypos;
		break;
	case MouseMoveType::CenteredDelta:
		unsigned int wx, wy;
		window->GetSize(&wx, &wy);
		x = mouse->_xpos - ((float)wx / 2.0f);
		y = mouse->_ypos - ((float)wy / 2.0f);
		break;
	default:
		break;
	}

	this->_action(x, y);
}