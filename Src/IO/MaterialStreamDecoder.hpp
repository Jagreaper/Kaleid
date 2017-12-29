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

namespace Kaleid::IO
{
	using MaterialStreamDecoder = DecoderBase<std::istream&, std::vector<Kaleid::Graphics::MaterialInfo>*, void*>;
}