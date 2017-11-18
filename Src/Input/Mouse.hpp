#pragma once

#include "stdafx.hpp"
#include "MouseBinding.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class Window;
}

API_BEGIN
namespace Kaleid::Input
{
	class KALEID_INPUT_API Mouse
	{
	public:
		Mouse();
		Mouse(const std::vector<MouseBinding>& mouse_bindings);
		Mouse(const std::vector<MouseBinding>* mouse_bindings);
		void Add(MouseBinding& mouse_binding);
		void Add(const std::vector<MouseBinding>& mouse_bindings);
		void Add(const std::vector<MouseBinding>* mouse_bindings);
		void Remove(const unsigned int index);
		void Clear();
		void Poll(Kaleid::Graphics::Window*& window);
		void GetPosition(double* xpos, double* ypos);
		void GetDeltaPosition(double* xpos, double* ypos);
		const double& GetPositionX() const;
		const double& GetPositionY() const;
		const double& GetDeltaPositionX() const;
		const double& GetDeltaPositionY() const;
	private:
		std::vector<MouseBinding> _mouse_bindings;
		double _xpos;
		double _ypos;
		double _old_xpos;
		double _old_ypos;
		double _delta_xpos;
		double _delta_ypos;

		friend class MouseBinding;
	};
}
API_END