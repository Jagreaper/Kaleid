#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "DecoderBase.hpp"
#include "Kaleid.Graphics\Material.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class GraphicsFactory;
}

namespace Kaleid::IO
{
	using MaterialStreamDecoder = StreamDecoderBase<std::vector<Kaleid::Graphics::MaterialInfo>*, void*>;
	using MaterialPathDecoder = PathDecoderBase<std::vector<Kaleid::Graphics::MaterialInfo>*, void*>;
}