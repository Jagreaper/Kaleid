#pragma once

namespace Kaleid::IO
{
	unsigned char* LoadImageFromFile(char const* file, int* width, int* height, int* channels, int req_comp);
	unsigned char* LoadImageFromMemory(unsigned char const* buffer, int length, int* width, int* height, int* channels, int req_comp);
	void FreeImage(unsigned char* data);
}