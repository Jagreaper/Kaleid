#include "stdafx.hpp"
#include "TextureBase.hpp"
#include <iostream>

using namespace Kaleid::Graphics;

TextureBase::TextureBase()
{
	glGenTextures(1, &this->_id);
	this->_width = 0;
	this->_height = 0;
	this->_type_info = 0;
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

bool TextureBase::Exists() const
{
	return this->_id != 0;
}

void TextureBase::Bind()
{
	glBindTexture(this->_type_info, this->_id);
}

void TextureBase::GenerateMipmap()
{
	this->Bind();
	glGenerateMipmap(this->_type_info);
}

void TextureBase::SetParameter(TextureParameter pname, int value)
{
	this->Bind();
	glTexParameteri(this->_type_info, static_cast<std::underlying_type_t<TextureParameter>>(pname), value);
}

void TextureBase::SetDefaultParameters()
{
	this->Bind();
	this->SetParameter(TextureParameter::WrapS, TextureWrap::Repeat);
	this->SetParameter(TextureParameter::WrapT, TextureWrap::Repeat);
	this->SetParameter(TextureParameter::MinFilter, TextureMinFilter::Linear);
	this->SetParameter(TextureParameter::MagFilter, TextureMagFilter::Linear);
}

#define TEXTURE_BASE_PARAMETER_SETTERS(TYPE) \
void TextureBase::SetParameter(TextureParameter pname, TYPE value) \
{ \
	this->Bind(); \
	glTexParameteri(this->_type_info, static_cast<std::underlying_type_t<TextureParameter>>(pname), static_cast<std::underlying_type_t<TYPE>>(value)); \
} \

TEXTURE_BASE_PARAMETER_SETTERS(DepthStencilTextureMode)
TEXTURE_BASE_PARAMETER_SETTERS(TextureCompareFunc)
TEXTURE_BASE_PARAMETER_SETTERS(TextureCompareMode)
TEXTURE_BASE_PARAMETER_SETTERS(TextureMinFilter)
TEXTURE_BASE_PARAMETER_SETTERS(TextureMagFilter)
TEXTURE_BASE_PARAMETER_SETTERS(TextureSwizzle)
TEXTURE_BASE_PARAMETER_SETTERS(TextureWrap)
TEXTURE_BASE_PARAMETER_SETTERS(TextureParameter)
TEXTURE_BASE_PARAMETER_SETTERS(InternalTextureFormat)
TEXTURE_BASE_PARAMETER_SETTERS(TextureFormat)
TEXTURE_BASE_PARAMETER_SETTERS(TextureDataType)

#undef TEXTURE_PARAMETER_SETTERS