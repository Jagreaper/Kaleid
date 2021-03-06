#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Graphics/BufferBase.hpp"
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class Renderer;
	class GraphicsFactory;

	class JAGERTS_KALEID_GRAPHICS_API VertexBuffer : public BufferBase
	{
	public:
#define _VERTEX_BUFFER_DATA_SETTER(TYPE) \
		void BufferData(const TYPE* data, size_t count, unsigned int stride, BufferUsage usage = BufferUsage::StaticDraw); \
		void BufferData(const std::vector<TYPE>* data, unsigned int stride, BufferUsage usage = BufferUsage::StaticDraw); \

		_VERTEX_BUFFER_DATA_SETTER(char)
		_VERTEX_BUFFER_DATA_SETTER(unsigned char)
		_VERTEX_BUFFER_DATA_SETTER(short)
		_VERTEX_BUFFER_DATA_SETTER(unsigned short)
		_VERTEX_BUFFER_DATA_SETTER(int)
		_VERTEX_BUFFER_DATA_SETTER(unsigned int)
		_VERTEX_BUFFER_DATA_SETTER(float)
		_VERTEX_BUFFER_DATA_SETTER(double)
#undef _VERTEX_BUFFER_DATA_SETTER
		const unsigned int GetStride() const;
	private:
		VertexBuffer();
		void Bind();

		unsigned int _stride;

		friend class GraphicsFactory;
		friend class Renderer;
	};
}