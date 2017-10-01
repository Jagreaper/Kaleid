#include "stdafx.hpp"
#include "BufferBase.hpp"

using namespace Kaleid::Graphics;


BufferBase::BufferBase()
{
	glGenBuffers(1, &this->_id);
	this->_length = 0;
}

const size_t BufferBase::GetLength() const
{
	return this->_length;
}

void BufferBase::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteBuffers(1, &this->_id);
		this->_id = 0;
	}
}
const bool BufferBase::Exists() const
{
	return this->_id != 0;
}