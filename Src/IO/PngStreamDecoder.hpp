#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include <istream>

API_BEGIN
namespace Kaleid::Imaging
{
	class Image;
}

namespace Kaleid::IO
{
	class KALEID_IO_API PngStreamDecoder : public DecoderBase<std::istream&, Kaleid::Imaging::Image, void>
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Imaging::Image* output, void* arg = NULL);
	};
}
API_END