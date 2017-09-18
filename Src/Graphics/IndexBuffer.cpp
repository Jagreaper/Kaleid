#include "stdafx.hpp"
#include "IndexBuffer.hpp"

using namespace Kaleid::Graphics;

IndexBuffer::IndexBuffer()
	: BufferBase()
{
	// Skip
}

void IndexBuffer::BufferData(const unsigned int* data, size_t count, BufferUsage usage)
{
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
	this->_length = count;
}

void IndexBuffer::BufferData(const std::vector<unsigned int>* data, BufferUsage usage)
{
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(unsigned int), data, usage);
	this->_length = data->size();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
}