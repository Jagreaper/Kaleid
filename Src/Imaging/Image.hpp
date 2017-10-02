#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Imaging
{
	class KALEID_IMAGING_API Image
	{
	public:
		Image(int byte_size);
		~Image();
	private:
		char* _data;
		int _byte_size;
	};
}
API_END