#pragma once

#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class Renderer
	{
	public:
		KALEID_GRAPHICS_API Renderer();
		KALEID_GRAPHICS_API void Load();
		KALEID_GRAPHICS_API void Dispose();
	};
}
API_END