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
	private:
		std::vector<MouseBinding> _mouse_bindings;
	};
}
API_END