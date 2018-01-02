#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"

namespace Kaleid::Graphics
{
	class Font;
}

namespace Kaleid::IO
{
	class KALEID_IO_API TrueFontDecoder : public Jagerts::Felcp::IO::DecoderBase<const char*, Kaleid::Graphics::Font*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Graphics::Font* output, void* arg);
	};
}