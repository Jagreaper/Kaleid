#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "ObjStreamDecoder.hpp"

namespace Kaleid::IO
{
	typedef DecoderBase<std::istream&, Kaleid::Game::Model, Kaleid::Graphics::GraphicsFactory> ModelStreamDecoder;

	class DecoderFactory
	{

	};
}