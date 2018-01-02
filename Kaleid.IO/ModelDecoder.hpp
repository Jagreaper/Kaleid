#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Kaleid.Graphics\Material.hpp"
#include <vector>

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
		std::vector<Kaleid::Graphics::MaterialInfo>* Materials = NULL; // TODO
		ModelDecoderParamsArg ModelDecoderParamsArg = ModelDecoderParamsArg::None;
	};

	using ModelStreamDecoder = Jagerts::Felcp::IO::StreamDecoderBase<Kaleid::Game::Model*, ModelDecoderParams&>;

	using ModelPathDecoder = Jagerts::Felcp::IO::PathDecoderBase<Kaleid::Game::Model*, ModelDecoderParams&>;
}