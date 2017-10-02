#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include <istream>

API_BEGIN
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
	class KALEID_IO_API HeightmapStreamDecoder : public DecoderBase<std::istream&, Kaleid::Game::Model, Kaleid::Graphics::GraphicsFactory>
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Game::Model* output, Kaleid::Graphics::GraphicsFactory* arg);
	};
}
API_END