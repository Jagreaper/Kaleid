#pragma once

#include "stdafx.hpp"
#include "GraphicsFactory.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class Renderer sealed
	{
	public:
		KALEID_GRAPHICS_API Renderer();
		KALEID_GRAPHICS_API void Load();
		KALEID_GRAPHICS_API void Dispose();

		KALEID_GRAPHICS_API void Clear(float red, float green, float blue, float alpha);
	};
}
API_END