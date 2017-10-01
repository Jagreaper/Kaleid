#include "stdafx.hpp"
#include "Keyboard.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;
using namespace Kaleid::Input;

Keyboard::Keyboard()
{
	// Skip
}

Keyboard::Keyboard(const std::vector<KeyBinding>& key_bindings)
{
	this->Add(key_bindings);
}

Keyboard::Keyboard(const std::vector<KeyBinding>* key_bindings)
{
	this->Add(key_bindings);
}

void Keyboard::Add(KeyBinding& key_binding)
{
	this->_key_bindings.push_back(key_binding);
}

void Keyboard::Add(const std::vector<KeyBinding>& key_bindings)
{
	VectorHelper::AddRange(this->_key_bindings, key_bindings);
}

void Keyboard::Add(const std::vector<KeyBinding>* key_bindings)
{
	VectorHelper::AddRange(this->_key_bindings, key_bindings);
}

void Keyboard::Remove(const unsigned int index)
{
	this->_key_bindings.erase(this->_key_bindings.begin() + index);
}

void Keyboard::Poll(Kaleid::Graphics::Window*& window)
{
	for (unsigned int index = 0; index < this->_key_bindings.size(); index++)
		this->_key_bindings[index].Poll(window);
}

void Keyboard::Clear()
{
	this->_key_bindings.clear();
}