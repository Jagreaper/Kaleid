#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Input/KeyBinding.hpp"
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class Window;
}

namespace Jagerts::Kaleid::Input
{
	class JAGERTS_KALEID_INPUT_API Keyboard
	{
	public:
		Keyboard();
		Keyboard(const std::vector<KeyBinding>& key_bindings);
		Keyboard(const std::vector<KeyBinding>* key_bindings);
		void Add(KeyBinding key_binding);
		void Add(const std::vector<KeyBinding>& key_bindings);
		void Add(const std::vector<KeyBinding>* key_bindings);
		void Remove(const unsigned int index);
		void Clear();
		void Poll(Jagerts::Kaleid::Graphics::Window*& window);
	private:
		std::vector<KeyBinding> _key_bindings;
	};
}