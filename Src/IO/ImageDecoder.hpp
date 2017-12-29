#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"

namespace Kaleid::Imaging
{
	class Image;
}

namespace Kaleid::IO
{
	class KALEID_IO_API ImagePathDecoder : public DecoderBase<const char*, Kaleid::Imaging::Image*, void*>
	{
	public:
		bool TryDecode(const char* source, Kaleid::Imaging::Image* output, void* arg);
	};
}