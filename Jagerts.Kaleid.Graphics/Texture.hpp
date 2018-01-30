#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Graphics/TextureBase.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class GraphicsFactory;

	class JAGERTS_KALEID_GRAPHICS_API Texture sealed : public TextureBase
	{
	public:
		jkgUsingTextureBase;
		void BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
	private:
		Texture();

		friend class GraphicsFactory;
	};
}