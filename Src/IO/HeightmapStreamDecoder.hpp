#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "ModelStreamDecoder.hpp"
#include <istream>

API_BEGIN
namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	class KALEID_IO_API HeightmapStreamDecoder : public ModelStreamDecoder
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
	};
}
API_END