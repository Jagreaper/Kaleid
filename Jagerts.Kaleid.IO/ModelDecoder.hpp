#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"
#include "Jagerts.Kaleid.Graphics/Material.hpp"
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class GraphicsFactory;
}

namespace Jagerts::Kaleid::Game
{
	class Model;
}

namespace Jagerts::Kaleid::IO
{
	enum class ModelDecoderParamsArg
	{
		None,
		Normalize,
		Center,
	};

	struct ModelDecoderParams
	{
		Jagerts::Kaleid::Graphics::GraphicsFactory* GraphicsFactory = NULL;
		std::vector<Jagerts::Kaleid::Graphics::MaterialInfo>* Materials = NULL; // TODO
		ModelDecoderParamsArg ModelDecoderParamsArg = ModelDecoderParamsArg::None;
	};

	using ModelDecoder = Jagerts::Felcp::IO::StreamPathDecoder<Jagerts::Kaleid::Game::Model*, ModelDecoderParams&>;

	using ModelStreamDecoder = Jagerts::Felcp::IO::StreamDecoderBase<Jagerts::Kaleid::Game::Model*, ModelDecoderParams&>;

	using ModelPathDecoder = Jagerts::Felcp::IO::PathDecoderBase<Jagerts::Kaleid::Game::Model*, ModelDecoderParams&>;
}