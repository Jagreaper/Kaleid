#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "ObjStreamDecoder.hpp"

namespace Kaleid::IO
{
	using ModelStreamDecoder = DecoderBase<std::istream&, Kaleid::Game::Model, Kaleid::Graphics::GraphicsFactory>;

	class DecoderFactory
	{

	};
}