#pragma once

#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API Renderer
	{
	public:
		void Load();
		void Dispose();
	};
}