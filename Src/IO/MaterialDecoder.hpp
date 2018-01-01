#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "Material.hpp"
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