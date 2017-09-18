#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class VertexBuffer sealed : public BufferBase
	{
		friend class GraphicsFactory;
	public:
#define _VERTEX_BUFFER_DATA_SETTER(TYPE) \
		KALEID_GRAPHICS_API void BufferData(const TYPE* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw); \
		KALEID_GRAPHICS_API void BufferData(const std::vector<TYPE>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw); \

		_VERTEX_BUFFER_DATA_SETTER(char)
		_VERTEX_BUFFER_DATA_SETTER(unsigned char)
		_VERTEX_BUFFER_DATA_SETTER(short)
		_VERTEX_BUFFER_DATA_SETTER(unsigned short)
		_VERTEX_BUFFER_DATA_SETTER(int)
		_VERTEX_BUFFER_DATA_SETTER(unsigned int)
		_VERTEX_BUFFER_DATA_SETTER(float)
		_VERTEX_BUFFER_DATA_SETTER(double)
#undef _VERTEX_BUFFER_DATA_SETTER
		KALEID_GRAPHICS_API const unsigned int GetPointSize() const;
	private:
		VertexBuffer();
		void Bind();

		unsigned int _point_size;
	};
}
API_END