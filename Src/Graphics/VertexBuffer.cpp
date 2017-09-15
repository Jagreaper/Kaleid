#include "stdafx.hpp"
#include "VertexBuffer.hpp"

using namespace Kaleid::Graphics;

VertexBuffer::VertexBuffer()
	: BufferBase()
{
	this->_point_size = 0;
	glGenBuffers(1, &this->_id);
}

VertexBuffer::VertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage)
	:VertexBuffer()
{
	this->BufferData(data, count, point_size, usage);
}

VertexBuffer::VertexBuffer(const std::vector<float>* data, unsigned int point_size, BufferUsage usage)
	: VertexBuffer()
{
	this->BufferData(data, point_size, usage);
}

VertexBuffer::~VertexBuffer()
{
	this->Dispose();
}

void VertexBuffer::BufferData(const float* data, size_t count, unsigned int point_size, BufferUsage usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, usage);
	this->_point_size = point_size;
	this->_length = count / point_size;
}

void VertexBuffer::BufferData(const std::vector<float>* data, unsigned int point_size, BufferUsage usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_id);
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data, usage);
	this->_point_size = point_size;
	this->_length = data->size() / point_size;
}

void VertexBuffer::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteBuffers(1, &this->_id);
		this->_id = 0;
	}
}

const unsigned int VertexBuffer::GetPointSize() const
{
	return this->_point_size;
}