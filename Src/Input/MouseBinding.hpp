#pragma once

#include "stdafx.hpp"
#include <functional>

namespace Kaleid::Graphics
{
	class Window;
}

namespace Kaleid::Input
{
	enum MouseCode
	{
		MouseButton1 = 0,
		MouseButton2 = 1,
		MouseButton3 = 2,
		MouseButton4 = 3,
		MouseButton5 = 4,
		MouseButton6 = 5,
		MouseButton7 = 6,
		MouseButton8 = 7,
		MouseButtonLast = MouseButton8,
		MouseButtonLeft = MouseButton1,
		MouseButtonMiddle = MouseButton3,
		MouseButtonRight = MouseButton2,
		MovedDelta = 8,
		Moved = 9,
	};

	enum MouseBindingState
	{
		MouseMoved,
		ButtonPressed,
		ButtonHeld,
		ButtonReleased,
		ButtonNotHeld,
	};

	API_BEGIN
		class KALEID_INPUT_API MouseBinding
	{
	public:
		MouseBinding(const MouseCode mouse_code, const MouseBindingState state, const std::function<void(double, double)> action);
		void Poll(Kaleid::Graphics::Window*& window);
	private:
		MouseCode _mouse_code;
		MouseBindingState _state;
		std::function<void(double, double)> _action;
		char _old_glfw_state;
		double _old_xpos;
		double _old_ypos;
	};
	API_END
}