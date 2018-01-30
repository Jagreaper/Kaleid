#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"
#include "Jagerts.Kaleid.Graphics/Material.hpp"
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class GraphicsFactory;
}

namespace Jagerts::Kaleid::IO
{
	using MaterialDecoder = Jagerts::Felcp::IO::StreamPathDecoder<std::vector<Jagerts::Kaleid::Graphics::MaterialInfo>*, void*>;
	using MaterialStreamDecoder = Jagerts::Felcp::IO::StreamDecoderBase<std::vector<Jagerts::Kaleid::Graphics::MaterialInfo>*, void*>;
	using MaterialPathDecoder = Jagerts::Felcp::IO::PathDecoderBase<std::vector<Jagerts::Kaleid::Graphics::MaterialInfo>*, void*>;
}