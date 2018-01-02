#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "ModelDecoder.hpp"
#include <istream>

namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	class KALEID_IO_API ObjModelDecoder : public ModelDecoder
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
		using ModelDecoder::TryDecode;
	};
}