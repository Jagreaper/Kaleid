#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "Material.hpp"
#include <vector>
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
		std::vector<Kaleid::Game::MaterialInfo>* Materials = NULL; // TODO
		bool Normalize = false;
		bool Center = true; // TODO
	};

	using ModelStreamDecoder = DecoderBase<std::istream&, Kaleid::Game::Model*, ModelDecoderParams&>;
}