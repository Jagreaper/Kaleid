#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class KALEID_GRAPHICS_API IndexBuffer sealed : public BufferBase
	{
	public:
#define _INDEX_BUFFER_DATA_SETTER(TYPE) \
		void BufferData(const TYPE* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw); \
		void BufferData(const std::vector<TYPE>* data, BufferUsage usage = BufferUsage::StaticDraw); \

		_INDEX_BUFFER_DATA_SETTER(unsigned char)
		_INDEX_BUFFER_DATA_SETTER(unsigned short)
		_INDEX_BUFFER_DATA_SETTER(unsigned int)
#undef _INDEX_BUFFER_DATA_SETTER
	private:
		IndexBuffer();
		void Bind();

		friend class GraphicsFactory;
	};
}
API_END