#pragma once

#include "stdafx.hpp"
#include "TextureBase.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class Texture : public TextureBase
	{
	public:
		void BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
		void GenerateMipmap();
		void SetParameter(TextureParameter pname, int value);
		void SetDefaultParameters();
#ifdef KALEID_GRAPHICS_DLL
		Texture();
		Texture(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
#endif
	};
}
API_END