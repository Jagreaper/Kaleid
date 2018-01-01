#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"

namespace Kaleid::Graphics
{
	class Font;
}

namespace Kaleid::IO
{
	class KALEID_IO_API TrueFontDecoder : public DecoderBase<const char*, Kaleid::Graphics::Font*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Graphics::Font* output, void* arg);
	};
}