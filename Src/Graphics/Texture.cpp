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
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, data);
}

void Texture::GenerateMipmap()
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetParameter(TextureParameter pname, int value)
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glTexParameteri(GL_TEXTURE_2D, pname, value);
}

void Texture::SetDefaultParameters()
{
	glBindTexture(GL_TEXTURE_2D, this->_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}