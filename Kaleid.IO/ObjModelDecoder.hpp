#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "ModelDecoder.hpp"
#include <istream>

namespace Kaleid::Game
{
	class Model;
}

namespace Kaleid::IO
{
	class KALEID_IO_API ObjModelStreamDecoder : public ModelStreamDecoder
	{
	public:
		bool TryDecode(std::istream& source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
	};

	class KALEID_IO_API ObjModelPathDecoder : public ModelPathDecoder
	{
	public:
		bool TryDecode(const char* source, Kaleid::Game::Model* output, ModelDecoderParams& arg);
	private:
		ObjModelStreamDecoder _stream_decoder;
	};
}