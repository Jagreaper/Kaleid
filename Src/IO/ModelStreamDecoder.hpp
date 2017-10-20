#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include <istream>

namespace Kaleid::Graphics
{
	class GraphicsFactory;
}

namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	struct ModelDecoderParams
	{
		Kaleid::Graphics::GraphicsFactory* GraphicsFactory = NULL;
		bool Normalize = false;
	};

	using ModelStreamDecoder = DecoderBase<std::istream&, Kaleid::Game::Model*, ModelDecoderParams&>;
}