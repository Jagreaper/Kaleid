#pragma once

#include "stdafx.hpp"
#include <functional>

namespace Kaleid::Graphics
{
	class Window;
}

namespace Kaleid::Input
{
	class Mouse;

	enum class MouseMoveType
	{
		Normal,
		Delta,
	};

	enum class MouseMoveBindingState
	{
		Normal,
		Centered,
	};

	class KALEID_INPUT_API MouseMoveBinding
	{
	public:
		MouseMoveBinding(const MouseMoveType _type, const MouseMoveBindingState state, const std::function<void(double, double)> action);
		void Poll(Kaleid::Graphics::Window*& window, Mouse* mouse);
	protected:
		MouseMoveType _type;
		MouseMoveBindingState _state;
		std::function<void(double, double)> _action;
		char _old_glfw_state;
	};
}