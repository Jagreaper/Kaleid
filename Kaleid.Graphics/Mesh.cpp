#include "Mesh.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "TextureBase.hpp"

using namespace Kaleid::Graphics;

Mesh::Mesh()
{
	this->_primitive_type = PrimitiveType::Triangles;
	glGenVertexArrays(1, &this->_vao_id);
}

void Mesh::Dispose()
{
	if (this->_vao_id != 0)
	{
		glDeleteVertexArrays(1, &this->_vao_id);
		this->_vao_id = 0;
	}
}

void Mesh::Compose()
{
#ifdef DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
#endif

	this->_b_vbo_length = 0;

	glBindVertexArray(this->_vao_id);
	for (unsigned int index = 0; index < (unsigned int)this->_vbos.size(); index++)
	{
		VertexBuffer* vbo = this->_vbos[index];
		glBindBuffer(GL_ARRAY_BUFFER, vbo->_id);
		if (vbo->GetLength() > this->_b_vbo_length)
			this->_b_vbo_length = vbo->GetLength();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, vbo->GetStride(), vbo->_type_info, GL_FALSE, 0, NULL);
	}
	glBindVertexArray(0);
}

void Mesh::SetIndexBuffer(IndexBuffer* buffer)
{
	this->_ibo = buffer;
}

void Mesh::SetVertexBuffers(const std::vector<VertexBuffer*>& buffers)
{
	this->_vbos.clear();
	for (unsigned int index = 0; index < (unsigned int)buffers.size(); index++)
		this->_vbos.push_back(buffers.at(index));
}

void Mesh::SetVertexBuffers(const std::vector<VertexBuffer*>* buffers)
{
	this->_vbos.clear();
	for (unsigned int index = 0; index < (unsigned int)buffers->size(); index++)
		this->_vbos.push_back(buffers->at(index));
}

void Mesh::SetVertexBuffers(VertexBuffer*& buffers, const unsigned int count)
{
	VertexBuffer* vbo = buffers;
	this->_vbos.clear();
	for (unsigned int index = 0; index < count; index++)
		this->_vbos.push_back(vbo++);
}

IndexBuffer* Mesh::GetIndexBuffer() const
{
	return this->_ibo;
}

const std::vector<VertexBuffer*>* Mesh::GetVertexBuffers() const
{
	return &this->_vbos;
}

const bool Mesh::HasIndexBuffer() const
{
	return this->_ibo != NULL;
}

const bool Mesh::HasVertexBuffers() const
{
	return this->_vbos.size() > 0;
}

void Mesh::SetPrimitiveType(const PrimitiveType type)
{
	this->_primitive_type = type;
}

const PrimitiveType Mesh::GetPrimitiveType() const
{
	return this->_primitive_type;
}