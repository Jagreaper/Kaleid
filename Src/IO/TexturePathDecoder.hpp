#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"

namespace Kaleid::Graphics
{
	class Texture;
}

API_BEGIN
namespace Kaleid::IO
{
	class KALEID_IO_API TexturePathDecoder : public DecoderBase<const char*, Kaleid::Graphics::Texture*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Graphics::Texture* output, void* arg);
	};
}
API_END