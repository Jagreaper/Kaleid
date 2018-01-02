#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Jagerts.Felcp.IO.Imaging\ImageDecoder.hpp"

namespace Kaleid::Graphics
{
	class Texture;
}

namespace Kaleid::IO
{
	class KALEID_IO_API TexturePathDecoder : public Jagerts::Felcp::IO::PathDecoderBase<Kaleid::Graphics::Texture*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Graphics::Texture* output, void* arg);
	private:
		Jagerts::Felcp::IO::Imaging::ImageDecoder _image_decoder;
	};
}