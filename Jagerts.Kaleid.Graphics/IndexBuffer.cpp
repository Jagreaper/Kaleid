#include "IndexBuffer.hpp"

using namespace Jagerts::Kaleid::Graphics;

IndexBuffer::IndexBuffer()
	: BufferBase()
{
	// Skip
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
}

#define INDEX_BUFFER_DATA_SETTER(TYPE, OGL_TYPE) \
void IndexBuffer::BufferData(const TYPE* data, size_t count, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(TYPE), data, usage); \
	this->_length = count; \
	this->_type_info = OGL_TYPE; \
} \
\
void IndexBuffer::BufferData(const std::vector<TYPE>* data, BufferUsage usage) \
{ \
	this->Bind(); \
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(TYPE), data, usage); \
	this->_length = data->size(); \
	this->_type_info = OGL_TYPE; \
} \

INDEX_BUFFER_DATA_SETTER(unsigned char, GL_UNSIGNED_BYTE)
INDEX_BUFFER_DATA_SETTER(unsigned short, GL_UNSIGNED_SHORT)
INDEX_BUFFER_DATA_SETTER(unsigned int, GL_UNSIGNED_INT)
#undef INDEX_BUFFER_DATA_SETTER