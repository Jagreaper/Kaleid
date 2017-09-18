#include "stdafx.hpp"
#include "Texture.hpp"

using namespace Kaleid::Graphics;

Texture::Texture()
{
	glGenTextures(1, &this->_id);
}

void Texture::BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format, TextureFormat format, TextureDataType type)
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<std::underlying_type_t<InternalTextureFormat>>(internal_format), width, height, 0, static_cast<std::underlying_type_t<TextureFormat>>(format), static_cast<std::underlying_type_t<TextureDataType>>(type), data);
}

void Texture::GenerateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetParameter(TextureParameter pname, int value)
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glTexParameteri(GL_TEXTURE_2D, static_cast<std::underlying_type_t<TextureParameter>>(pname), value);
}

void Texture::SetDefaultParameters()
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

#define TEXTURE_PARAMETER_SETTERS(OGL_TYPE) \
void Texture::SetParameter(TextureParameter pname, OGL_TYPE value) \
{ \
	glBindTexture(GL_TEXTURE_2D, this->_id); \
	glTexParameteri(GL_TEXTURE_2D, static_cast<std::underlying_type_t<TextureParameter>>(pname), static_cast<std::underlying_type_t<OGL_TYPE>>(value)); \
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
