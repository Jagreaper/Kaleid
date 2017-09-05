#include "stdafx.hpp"
#include "BufferBase.hpp"

using namespace Kaleid::Graphics;

const unsigned int BufferBase::GetId() const
{
	return this->_id;
}

const size_t BufferBase::GetLength() const
{
	return this->_length;
}