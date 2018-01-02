#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "TextureBase.hpp"

namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class KALEID_GRAPHICS_API Texture sealed : public TextureBase
	{
	public:
		void BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
	private:
		Texture();

		friend class GraphicsFactory;
	};
}