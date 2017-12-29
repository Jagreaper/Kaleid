#pragma once

#include "stdafx.hpp"
#include "KeyBinding.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class Window;
}

namespace Kaleid::Input
{
	class KALEID_INPUT_API Keyboard
	{
	public:
		Keyboard();
		Keyboard(const std::vector<KeyBinding>& key_bindings);
		Keyboard(const std::vector<KeyBinding>* key_bindings);
		void Add(KeyBinding& key_binding);
		void Add(const std::vector<KeyBinding>& key_bindings);
		void Add(const std::vector<KeyBinding>* key_bindings);
		void Remove(const unsigned int index);
		void Clear();
		void Poll(Kaleid::Graphics::Window*& window);
	private:
		std::vector<KeyBinding> _key_bindings;
	};
}