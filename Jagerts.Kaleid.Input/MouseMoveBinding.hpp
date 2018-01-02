#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include <functional>

namespace Jagerts::Kaleid::Graphics
{
	class Window;
}

namespace Jagerts::Kaleid::Input
{
	class Mouse;

	enum class MouseMoveType
	{
		Normal,
		Delta,
		CenteredDelta,
	};

	class JAGERTS_KALEID_INPUT_API MouseMoveBinding
	{
	public:
		MouseMoveBinding(const MouseMoveType type, const std::function<void(double, double)> action);
		void Poll(Jagerts::Kaleid::Graphics::Window*& window, Mouse* mouse);
	protected:
		MouseMoveType _type;
		std::function<void(double, double)> _action;
		char _old_glfw_state;
	};
}