#include "TextureDecoder.hpp"
#include "Kaleid.Graphics\Texture.hpp"
#include "ImageLoader.hpp"
#include "STB\stb_image.h"
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Graphics;

bool TexturePathDecoder::TryDecode(const char* source, Texture* output, void* arg)
{
	int width, height, comp;
	unsigned char* data = LoadImageFromFile(source, &width, &height, &comp, STBI_rgb_alpha);
	int data_length = width * height * comp;

	if (comp == 3)
		output->BufferImage(data, width, height, InternalTextureFormat::Rgba, TextureFormat::Rgb);
	else if (comp == 4)
		output->BufferImage(data, width, height, InternalTextureFormat::Rgba, TextureFormat::Rgba);
	else
		throw new std::runtime_error("Cannot read Grayscale image into OpenGL");

	output->SetDefaultParameters();

	return true;
}