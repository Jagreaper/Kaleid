#pragma once

#include "stdafx.hpp"
#include "TextureBase.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class KALEID_GRAPHICS_API Texture sealed : public TextureBase
	{
	public:
		void BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
		void GenerateMipmap();
		void SetDefaultParameters();
		void SetParameter(TextureParameter pname, int value);

#define _TEXTURE_PARAMETER_SETTERS(TYPE) \
		void SetParameter(TextureParameter pname, TYPE value); \

		_TEXTURE_PARAMETER_SETTERS(DepthStencilTextureMode)
		_TEXTURE_PARAMETER_SETTERS(TextureCompareFunc)
		_TEXTURE_PARAMETER_SETTERS(TextureCompareMode)
		_TEXTURE_PARAMETER_SETTERS(TextureMinFilter)
		_TEXTURE_PARAMETER_SETTERS(TextureMagFilter)
		_TEXTURE_PARAMETER_SETTERS(TextureSwizzle)
		_TEXTURE_PARAMETER_SETTERS(TextureWrap)
		_TEXTURE_PARAMETER_SETTERS(TextureParameter)
		_TEXTURE_PARAMETER_SETTERS(InternalTextureFormat)
		_TEXTURE_PARAMETER_SETTERS(TextureFormat)
		_TEXTURE_PARAMETER_SETTERS(TextureDataType)
#undef _TEXTURE_PARAMETER_SETTERS
	private:
		Texture();
		void Bind();

		friend class GraphicsFactory;
	};
}
API_END