#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include <vector>
#include <string>

namespace Jagerts::Kaleid::Graphics
{
	class JAGERTS_KALEID_GRAPHICS_API Glyph
	{
	public:

	private:
		char _char;
		std::vector<unsigned int> _data;
	};

	class JAGERTS_KALEID_GRAPHICS_API Font
	{

	};
}