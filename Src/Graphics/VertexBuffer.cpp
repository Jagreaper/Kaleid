#include "stdafx.hpp"
#include "VertexBuffer.hpp"

using namespace Kaleid::Graphics;

VertexBuffer::VertexBuffer()
	: BufferBase()
{
	this->_point_size = 0;
}

#define VERTEX_BUFFER_DATA_SETTER(TYPE, GL_TYPE) \
void VertexBuffer::BufferData(const TYPE* data, size_t count, unsigned int point_size, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(TYPE), data, usage); \
	this->_point_size = point_size; \
	this->_length = count / point_size; \
	int _type_info = GL_TYPE;\
} \
\
void VertexBuffer::BufferData(const std::vector<TYPE>* data, unsigned int point_size, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(TYPE), data, usage); \
	this->_point_size = point_size; \
	this->_length = data->size() / point_size; \
	int _type_info = GL_TYPE; \
} \

VERTEX_BUFFER_DATA_SETTER(char, GL_BYTE)
VERTEX_BUFFER_DATA_SETTER(unsigned char, GL_UNSIGNED_BYTE)
VERTEX_BUFFER_DATA_SETTER(short, GL_SHORT)
VERTEX_BUFFER_DATA_SETTER(unsigned short, GL_UNSIGNED_SHORT)
VERTEX_BUFFER_DATA_SETTER(int, GL_INT)
VERTEX_BUFFER_DATA_SETTER(unsigned int, GL_UNSIGNED_INT)
VERTEX_BUFFER_DATA_SETTER(float, GL_FLOAT)
VERTEX_BUFFER_DATA_SETTER(double, GL_DOUBLE)
#undef VERTEX_BUFFER_DATA_SETTER

const unsigned int VertexBuffer::GetPointSize() const
{
	return this->_point_size;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_id);
}