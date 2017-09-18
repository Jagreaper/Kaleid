#pragma once

#include "stdafx.hpp"
#include "TextureBase.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class Texture sealed : public TextureBase
	{
	public:
		KALEID_GRAPHICS_API void BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format = InternalTextureFormat::Rgb, TextureFormat format = TextureFormat::Rgb, TextureDataType type = TextureDataType::UnsignedByte);
		KALEID_GRAPHICS_API void GenerateMipmap();
		KALEID_GRAPHICS_API void SetDefaultParameters();
		KALEID_GRAPHICS_API void SetParameter(TextureParameter pname, int value);

#define _TEXTURE_PARAMETER_SETTERS(TYPE) KALEID_GRAPHICS_API void SetParameter(TextureParameter pname, TYPE value);
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
#ifdef KALEID_GRAPHICS_DLL
		Texture();
		
		void Bind();
#endif
	};
}
API_END