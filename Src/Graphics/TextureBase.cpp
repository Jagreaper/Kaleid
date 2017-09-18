#include "stdafx.hpp"
#include "TextureBase.hpp"

using namespace Kaleid::Graphics;

TextureBase::TextureBase()
{
	glGenTextures(1, &this->_id);
	this->_width = 0;
	this->_height = 0;
}

const unsigned int TextureBase::GetWidth() const
{
	return this->_width;
}

const unsigned int TextureBase::GetHeight() const
{
	return this->_height;
}

void TextureBase::GetSize(unsigned int* width, unsigned int* height) const
{
	*width = this->_width;
	*height = this->_height;
}

void TextureBase::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteTextures(1, &this->_id);
		this->_id = 0;
	}
}

const unsigned int TextureBase::GetId() const
{
	return this->_id;
}