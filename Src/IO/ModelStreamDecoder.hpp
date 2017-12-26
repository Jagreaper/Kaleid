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
	enum class ModelDecoderParamsArg
	{
		None,
		Normalize,
		Center,
	};

	struct ModelDecoderParams
	{
		Kaleid::Graphics::GraphicsFactory* GraphicsFactory = NULL;
		std::vector<Kaleid::Game::MaterialInfo>* Materials = NULL; // TODO
		ModelDecoderParamsArg ModelDecoderParamsArg = ModelDecoderParamsArg::None;
	};

	using ModelStreamDecoder = DecoderBase<std::istream&, Kaleid::Game::Model*, ModelDecoderParams&>;
}