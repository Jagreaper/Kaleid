#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include <functional>

namespace Jagerts::Kaleid::Graphics
{
	class Window;
}

namespace Jagerts::Kaleid::Input
{
	class Mouse;

	enum MouseClickCode
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

	enum MouseClickBindingState
	{
		MouseMoved,
		ButtonPressed,
		ButtonHeld,
		ButtonReleased,
		ButtonNotHeld,
	};

	class JAGERTS_KALEID_INPUT_API MouseClickBinding
	{
	public:
		MouseClickBinding(const MouseClickCode mouse_code, const MouseClickBindingState state, const std::function<void()> action);
	    void Poll(Jagerts::Kaleid::Graphics::Window*& window, Mouse* mouse);
	protected:
		MouseClickCode _mouse_code;
		MouseClickBindingState _state;
		std::function<void()> _action;
		char _old_glfw_state;
	};
}