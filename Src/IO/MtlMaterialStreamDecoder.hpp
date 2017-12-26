#pragma once

#include "stdafx.hpp"
#include "DecoderBase.hpp"
#include "MaterialStreamDecoder.hpp"
#include "Material.hpp"
#include <istream>

API_BEGIN
namespace Kaleid::IO
{
	class KALEID_IO_API MtlMaterialStreamDecoder : public MaterialStreamDecoder
	{
	public:
		bool TryDecode(std::istream& source, std::vector<Kaleid::Graphics::MaterialInfo>* output, void* arg);
	};
}
API_END