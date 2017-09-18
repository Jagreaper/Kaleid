#include "stdafx.hpp"
#include "IndexBuffer.hpp"

using namespace Kaleid::Graphics;

IndexBuffer::IndexBuffer()
	: BufferBase()
{
	// Skip
}

#define INDEX_BUFFER_DATA_SETTER(TYPE, GL_TYPE) \
void IndexBuffer::BufferData(const TYPE* data, size_t count, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(TYPE), data, usage); \
	this->_length = count; \
	int _type_info = GL_TYPE; \
} \
\
void IndexBuffer::BufferData(const std::vector<TYPE>* data, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(TYPE), data, usage); \
	this->_length = data->size(); \
	int _type_info = GL_TYPE; \
} \

INDEX_BUFFER_DATA_SETTER(unsigned char, GL_UNSIGNED_BYTE)
INDEX_BUFFER_DATA_SETTER(unsigned short, GL_UNSIGNED_SHORT)
INDEX_BUFFER_DATA_SETTER(unsigned int, GL_UNSIGNED_INT)
#undef INDEX_BUFFER_DATA_SETTER

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
}