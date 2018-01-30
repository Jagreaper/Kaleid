#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.IO/MaterialDecoder.hpp"
#include <istream>

namespace Jagerts::Kaleid::IO
{
	class JAGERTS_KALEID_IO_API MtlMaterialDecoder : public MaterialDecoder
	{
	public:
		bool TryDecode(std::istream& source, std::vector<Jagerts::Kaleid::Graphics::MaterialInfo>* output, void* arg);
		using MaterialDecoder::TryDecode;
	};
}