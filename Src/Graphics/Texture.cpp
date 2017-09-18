#include "stdafx.hpp"
#include "Texture.hpp"

using namespace Kaleid::Graphics;

Texture::Texture()
	: TextureBase()
{
	// Skip
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
}

void Texture::BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format, TextureFormat format, TextureDataType type)
{
	this->Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<std::underlying_type_t<InternalTextureFormat>>(internal_format), width, height, 0, static_cast<std::underlying_type_t<TextureFormat>>(format), static_cast<std::underlying_type_t<TextureDataType>>(type), data);
}

void Texture::GenerateMipmap()
{
	this->Bind();
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetParameter(TextureParameter pname, int value)
{
	this->Bind();
	glTexParameteri(GL_TEXTURE_2D, static_cast<std::underlying_type_t<TextureParameter>>(pname), value);
}

void Texture::SetDefaultParameters()
{
	this->Bind();
	this->SetParameter(TextureParameter::WrapS, TextureWrap::Repeat);
	this->SetParameter(TextureParameter::WrapT, TextureWrap::Repeat);
	this->SetParameter(TextureParameter::MinFilter, TextureMinFilter::Linear);
	this->SetParameter(TextureParameter::MagFilter, TextureMagFilter::Linear);
}

#define TEXTURE_PARAMETER_SETTERS(TYPE) \
void Texture::SetParameter(TextureParameter pname, TYPE value) \
{ \
	this->Bind(); \
	glTexParameteri(GL_TEXTURE_2D, static_cast<std::underlying_type_t<TextureParameter>>(pname), static_cast<std::underlying_type_t<TYPE>>(value)); \
} \

TEXTURE_PARAMETER_SETTERS(DepthStencilTextureMode)
TEXTURE_PARAMETER_SETTERS(TextureCompareFunc)
TEXTURE_PARAMETER_SETTERS(TextureCompareMode)
TEXTURE_PARAMETER_SETTERS(TextureMinFilter)
TEXTURE_PARAMETER_SETTERS(TextureMagFilter)
TEXTURE_PARAMETER_SETTERS(TextureSwizzle)
TEXTURE_PARAMETER_SETTERS(TextureWrap)
TEXTURE_PARAMETER_SETTERS(TextureParameter)
TEXTURE_PARAMETER_SETTERS(InternalTextureFormat)
TEXTURE_PARAMETER_SETTERS(TextureFormat)
TEXTURE_PARAMETER_SETTERS(TextureDataType)

#undef TEXTURE_PARAMETER_SETTERS
