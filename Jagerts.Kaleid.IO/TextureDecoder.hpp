#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Jagerts.Felcp.IO.Imaging\ImageDecoder.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class Texture;
}

namespace Jagerts::Kaleid::IO
{
	class JAGERTS_KALEID_IO_API TextureDecoder : public Jagerts::Felcp::IO::PathDecoderBase<Jagerts::Kaleid::Graphics::Texture*, void*>
	{
	public:
		bool TryDecode(const char* source, Jagerts::Kaleid::Graphics::Texture* output, void* arg);
	private:
		Jagerts::Felcp::IO::Imaging::ImageDecoder _image_decoder;
	};
}