#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include <vector>
#include <istream>

namespace Kaleid::Graphics
{
	class GraphicsFactory;
}
namespace Kaleid::Game
{
	class Material;
}

namespace Kaleid::IO
{
	using MaterialStreamDecoder = DecoderBase<std::istream&, std::vector<Kaleid::Game::Material>*, void*>;
}