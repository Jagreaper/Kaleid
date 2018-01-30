#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.IO/ModelDecoder.hpp"
#include <istream>

namespace Jagerts::Kaleid::Game
{
	class Model;
}

namespace Jagerts::Kaleid::IO
{
	class JAGERTS_KALEID_IO_API ObjModelDecoder : public ModelDecoder
	{
	public:
		bool TryDecode(std::istream& source, Jagerts::Kaleid::Game::Model* output, ModelDecoderParams& arg);
		using ModelDecoder::TryDecode;
	};
}