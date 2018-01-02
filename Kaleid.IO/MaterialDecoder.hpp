#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"
#include "Kaleid.Graphics\Material.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class GraphicsFactory;
}

namespace Kaleid::IO
{
	using MaterialStreamDecoder = Jagerts::Felcp::IO::StreamDecoderBase<std::vector<Kaleid::Graphics::MaterialInfo>*, void*>;
	using MaterialPathDecoder = Jagerts::Felcp::IO::PathDecoderBase<std::vector<Kaleid::Graphics::MaterialInfo>*, void*>;
}