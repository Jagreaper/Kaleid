#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Input/MouseMoveBinding.hpp"
#include "Jagerts.Kaleid.Input/MouseClickBinding.hpp"
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class Window;
}

namespace Jagerts::Kaleid::Input
{
	class JAGERTS_KALEID_INPUT_API Mouse
	{
	public:
		Mouse();
		Mouse(const std::vector<MouseMoveBinding>& mouse_bindings);
		Mouse(const std::vector<MouseMoveBinding>* mouse_bindings);
		Mouse(const std::vector<MouseClickBinding>& mouse_bindings);
		Mouse(const std::vector<MouseClickBinding>* mouse_bindings);
		void Add(MouseMoveBinding mouse_binding);
		void Add(MouseClickBinding mouse_binding);
		void Add(const std::vector<MouseMoveBinding>& mouse_bindings);
		void Add(const std::vector<MouseMoveBinding>* mouse_bindings);
		void Add(const std::vector<MouseClickBinding>& mouse_bindings);
		void Add(const std::vector<MouseClickBinding>* mouse_bindings);
		void Remove(const unsigned int index);
		void Clear();
		void Poll(Jagerts::Kaleid::Graphics::Window*& window);
		void GetPosition(double* xpos, double* ypos);
		void GetDeltaPosition(double* xpos, double* ypos);
		const double& GetPositionX() const;
		const double& GetPositionY() const;
		const double& GetDeltaPositionX() const;
		const double& GetDeltaPositionY() const;
	private:
		std::vector<MouseMoveBinding> _mouse_move_bindings;
		std::vector<MouseClickBinding> _mouse_click_bindings;
		double _xpos;
		double _ypos;
		double _old_xpos;
		double _old_ypos;
		double _delta_xpos;
		double _delta_ypos;
		double _center_delta_xpos;
		double _center_delta_ypos;

		friend class MouseMoveBinding;
	};
}