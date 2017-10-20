#include "stdafx.hpp"
#include "HeightmapStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include <Windows.h>
#include <string>
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;

bool HeightmapStreamDecoder::TryDecode(std::istream& source, Model* output, ModelDecoderParams& arg)
{
	throw std::runtime_error("Not yet implemented");
}