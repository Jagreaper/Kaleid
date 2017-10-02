#pragma once

#include "stdafx.hpp"

namespace Kaleid::Input
{
	unsigned char* LoadImage(char const* file, int* width, int* height, int* channels, int req_comp);
	void FreeImage(unsigned char* data);
}