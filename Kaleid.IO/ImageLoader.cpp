#include "ImageLoader.hpp"

#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

unsigned char* Kaleid::IO::LoadImageFromFile(char const* file, int* width, int* height, int* channels, int req_comp)
{
	return stbi_load(file, width, height, channels, req_comp);
}

unsigned char* Kaleid::IO::LoadImageFromMemory(unsigned char const* buffer, int length, int* width, int* height, int* channels, int req_comp)
{
	return stbi_load_from_memory(buffer, length, width, height, channels, req_comp);
}

void Kaleid::IO::FreeImage(unsigned char* data)
{
	stbi_image_free(data);
}