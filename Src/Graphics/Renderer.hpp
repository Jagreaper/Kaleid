#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API Renderer sealed
	{
	public:
		Renderer();
		void Load();
		void Dispose();

		void Clear(float red, float green, float blue, float alpha);
	};
}
API_END