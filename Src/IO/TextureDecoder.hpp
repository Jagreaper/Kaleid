#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"

namespace Kaleid::Graphics
{
	class Texture;
}

namespace Kaleid::IO
{
	class KALEID_IO_API TexturePathDecoder : public PathDecoderBase<Kaleid::Graphics::Texture*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Graphics::Texture* output, void* arg);
	};
}