#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "ModelStreamDecoder.hpp"
#include <istream>

namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	class KALEID_IO_API ObjModelStreamDecoder : public ModelStreamDecoder
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
	};
}