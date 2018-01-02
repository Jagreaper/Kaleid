#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Jagerts.Felcp.IO.Imaging\ImageDecoder.hpp"
#include "ModelDecoder.hpp"
#include <istream>

namespace Jagerts::Kaleid::Game
{
	class Model;
}

namespace Jagerts::Kaleid::IO
{
	class JAGERTS_KALEID_IO_API HeightmapDecoder : public ModelPathDecoder
	{
	public:
		bool TryDecode(const char* source, Jagerts::Kaleid::Game::Model* output, ModelDecoderParams& arg);
	private:
		Jagerts::Felcp::IO::Imaging::ImageDecoder _image_decoder;
	};
}