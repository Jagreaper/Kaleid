#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "BufferBase.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class Renderer;
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
		friend class Renderer;
	};
}