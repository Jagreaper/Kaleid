#pragma once

#include "Kaleid.Shared\Common.hpp"
#include <vector>
#include <string>

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API Glyph
	{
	public:

	private:
		char _char;
		std::vector<unsigned int> _data;
	};

	class KALEID_GRAPHICS_API Font
	{

	};
}