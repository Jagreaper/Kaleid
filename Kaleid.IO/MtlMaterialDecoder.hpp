#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "MaterialDecoder.hpp"
#include <istream>

namespace Kaleid::IO
{
	class KALEID_IO_API MtlMaterialDecoder : public MaterialDecoder
	{
	public:
		bool TryDecode(std::istream& source, std::vector<Kaleid::Graphics::MaterialInfo>* output, void* arg);
		using MaterialDecoder::TryDecode;
	};
}