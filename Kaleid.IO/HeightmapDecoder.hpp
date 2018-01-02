#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Jagerts.Felcp.IO.Imaging\ImageDecoder.hpp"
#include "ModelDecoder.hpp"
#include <istream>

namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	class KALEID_IO_API HeightmapPathDecoder : public ModelPathDecoder
	{
	public:
		bool TryDecode(const char* source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
	private:
		Jagerts::Felcp::IO::Imaging::ImageDecoder _image_decoder;
	};
}