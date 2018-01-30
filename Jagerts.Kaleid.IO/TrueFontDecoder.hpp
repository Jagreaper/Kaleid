#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class Font;
}

namespace Jagerts::Kaleid::IO
{
	class JAGERTS_KALEID_IO_API TrueFontDecoder : public Jagerts::Felcp::IO::StreamPathDecoder<Jagerts::Kaleid::Graphics::Font*, void*>
	{
	public:
		bool TryDecode(std::istream& source, Jagerts::Kaleid::Graphics::Font* output, void* arg);
		using Jagerts::Felcp::IO::StreamPathDecoder<Jagerts::Kaleid::Graphics::Font*, void*>::TryDecode;
	};
}