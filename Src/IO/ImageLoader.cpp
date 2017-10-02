#include "stdafx.hpp"
#include "ImageLoader.h"

#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

unsigned char* Kaleid::Input::LoadImage(char const* file, int* width, int* height, int* channels, int req_comp)
{
	return stbi_load(file, width, height, channels, req_comp);
}

void Kaleid::Input::FreeImage(unsigned char* data)
{
	stbi_image_free(data);
}