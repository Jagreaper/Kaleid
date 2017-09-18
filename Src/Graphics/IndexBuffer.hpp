#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class IndexBuffer sealed : public BufferBase
	{
		friend class GraphicsFactory;
	public:
#define _INDEX_BUFFER_DATA_SETTER(TYPE) \
		KALEID_GRAPHICS_API void BufferData(const TYPE* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw); \
		KALEID_GRAPHICS_API void BufferData(const std::vector<TYPE>* data, BufferUsage usage = BufferUsage::StaticDraw); \

		_INDEX_BUFFER_DATA_SETTER(unsigned char)
		_INDEX_BUFFER_DATA_SETTER(unsigned short)
		_INDEX_BUFFER_DATA_SETTER(unsigned int)
#undef _INDEX_BUFFER_DATA_SETTER
	private:
		IndexBuffer();
		void Bind();
	};
}
API_END