#include "TextureDecoder.hpp"
#include "Kaleid.Graphics\Texture.hpp"
#include "STB\stb_image.h"
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Graphics;
using namespace Jagerts::Felcp::IO::Imaging;

bool TextureDecoder::TryDecode(const char* source, Texture* output, void* arg)
{
	RawImageData data;
	this->_image_decoder.TryDecode(source, &data);

	if (data.GetPixelSize() == 3)
		output->BufferImage(data.GetData(), data.GetWidth(), data.GetHeight(), InternalTextureFormat::Rgba, TextureFormat::Rgb);
	else if (data.GetPixelSize() == 4)
		output->BufferImage(data.GetData(), data.GetWidth(), data.GetHeight(), InternalTextureFormat::Rgba, TextureFormat::Rgba);
	else
		throw new std::runtime_error("Cannot read Grayscale image into OpenGL");

	output->SetDefaultParameters();
	RawImageData::Free(&data);

	return true;
}