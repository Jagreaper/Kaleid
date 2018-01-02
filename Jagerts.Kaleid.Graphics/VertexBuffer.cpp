#include "VertexBuffer.hpp"

using namespace Jagerts::Kaleid::Graphics;

VertexBuffer::VertexBuffer()
	: BufferBase()
{
	this->_stride = 0;
}

#define VERTEX_BUFFER_DATA_SETTER(TYPE, OGL_TYPE) \
void VertexBuffer::BufferData(const TYPE* data, size_t count, unsigned int stride, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(TYPE), data, usage); \
	this->_stride = stride; \
	this->_length = count / stride; \
	this->_type_info = OGL_TYPE;\
} \
\
void VertexBuffer::BufferData(const std::vector<TYPE>* data, unsigned int stride, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(TYPE), data, usage); \
	this->_stride = stride; \
	this->_length = data->size() / stride; \
	this->_type_info = OGL_TYPE; \
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

const unsigned int VertexBuffer::GetStride() const
{
	return this->_stride;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_id);
}