#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "GraphicsFactory.hpp"
#include <istream>

namespace Kaleid::IO
{
	class KALEID_IO_API ObjStreamDecoder : public DecoderBase<std::istream&, Kaleid::Graphics::GraphicsFactory, Kaleid::Graphics::Mesh>
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Graphics::Mesh* output, Kaleid::Graphics::GraphicsFactory* arg);
	};
}