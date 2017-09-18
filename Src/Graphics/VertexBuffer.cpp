#include "stdafx.hpp"
#include "VertexBuffer.hpp"

using namespace Kaleid::Graphics;

VertexBuffer::VertexBuffer()
	: BufferBase()
{
	this->_point_size = 0;
}

void VertexBuffer::BufferData(const float* data, size_t count, unsigned int point_size, BufferUsage usage)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, usage);
	this->_point_size = point_size;
	this->_length = count / point_size;
}

void VertexBuffer::BufferData(const std::vector<float>* data, unsigned int point_size, BufferUsage usage)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data, usage);
	this->_point_size = point_size;
	this->_length = data->size() / point_size;
}

const unsigned int VertexBuffer::GetPointSize() const
{
	return this->_point_size;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_id);
}