#include "stdafx.hpp"
#include "Texture.hpp"

using namespace Kaleid::Graphics;

Texture::Texture()
	: TextureBase()
{
	this->_type_info = GL_TEXTURE_2D;
}

void Texture::BufferImage(unsigned char* data, unsigned int width, unsigned int height, InternalTextureFormat internal_format, TextureFormat format, TextureDataType type)
{
	this->Bind();
	glTexImage2D(this->_type_info, 0, static_cast<std::underlying_type_t<InternalTextureFormat>>(internal_format), width, height, 0, static_cast<std::underlying_type_t<TextureFormat>>(format), static_cast<std::underlying_type_t<TextureDataType>>(type), data);
}
