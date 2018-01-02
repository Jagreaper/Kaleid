#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "DecoderBase.hpp"
#include "MaterialDecoder.hpp"
#include <istream>

namespace Kaleid::IO
{
	class KALEID_IO_API MtlMaterialStreamDecoder : public MaterialStreamDecoder
	{
	public:
		bool TryDecode(std::istream& source, std::vector<Kaleid::Graphics::MaterialInfo>* output, void* arg);
	};

	class KALEID_IO_API MtlMaterialPathDecoder : public MaterialPathDecoder
	{
	public:
		bool TryDecode(const char* source, std::vector<Kaleid::Graphics::MaterialInfo>* output, void* arg);
	private:
		MtlMaterialStreamDecoder _stream_decoder;
	};
}