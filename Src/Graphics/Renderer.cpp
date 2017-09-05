#include "stdafx.hpp"
#include "Renderer.hpp"

using namespace Kaleid::Graphics;

GraphicsFactory* Renderer::GetGraphicsFactory()
{
	if (this->_graphics_factory == NULL)
		this->_graphics_factory = this->CreateGraphicsFactory();

	return this->_graphics_factory;
}