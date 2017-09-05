#pragma once

#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API Renderer abstract
	{
	public:
		virtual void Load() = 0;
		virtual void Dispose() = 0;

		GraphicsFactory* GetGraphicsFactory();
	protected:
		virtual GraphicsFactory* CreateGraphicsFactory() = 0;

		GraphicsFactory* _graphics_factory;
	};
}