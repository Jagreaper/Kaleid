#include "stdafx.hpp"
#include "IndexBuffer.hpp"

using namespace Kaleid::Graphics;

IndexBuffer::IndexBuffer()
	: BufferBase()
{
	glGenBuffers(1, &this->_id);
}

IndexBuffer::IndexBuffer(const unsigned int* data, size_t count, BufferUsage usage)
	: IndexBuffer()
{
	this->BufferData(data, count, usage);
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>* data, BufferUsage usage)
	: IndexBuffer()
{
	this->BufferData(data, usage);
}

IndexBuffer::~IndexBuffer()
{
	this->Dispose();
}

void IndexBuffer::BufferData(const unsigned int* data, size_t count, BufferUsage usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
	this->_length = count;
}

void IndexBuffer::BufferData(const std::vector<unsigned int>* data, BufferUsage usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(unsigned int), data, usage);
	this->_length = data->size();
}

void IndexBuffer::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteBuffers(1, &this->_id);
		this->_id = 0;
	}
}