#include "stdafx.hpp"
#include "BufferBase.hpp"

using namespace Kaleid::Graphics;


BufferBase::BufferBase()
{
	this->_id = 0;
	this->_length = 0;
}

const unsigned int BufferBase::GetId() const
{
	return this->_id;
}

const size_t BufferBase::GetLength() const
{
	return this->_length;
}