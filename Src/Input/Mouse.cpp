#include "stdafx.hpp"
#include "Mouse.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;
using namespace Kaleid::Input;

Mouse::Mouse()
{
	// Skip
}

Mouse::Mouse(const std::vector<MouseBinding>& mouse_bindings)
{
	this->Add(mouse_bindings);
}

Mouse::Mouse(const std::vector<MouseBinding>* mouse_bindings)
{
	this->Add(mouse_bindings);
}

void Mouse::Add(MouseBinding& mouse_binding)
{
	this->_mouse_bindings.push_back(mouse_binding);
}

void Mouse::Add(const std::vector<MouseBinding>& mouse_bindings)
{
	VectorHelper::AddRange(this->_mouse_bindings, mouse_bindings);
}

void Mouse::Add(const std::vector<MouseBinding>* mouse_bindings)
{
	VectorHelper::AddRange(this->_mouse_bindings, mouse_bindings);
}

void Mouse::Remove(const unsigned int index)
{
	this->_mouse_bindings.erase(this->_mouse_bindings.begin() + index);
}

void Mouse::Poll(Kaleid::Graphics::Window*& window)
{
	for (unsigned int index = 0; index < this->_mouse_bindings.size(); index++)
		this->_mouse_bindings[index].Poll(window);
}

void Mouse::Clear()
{
	this->_mouse_bindings.clear();
}