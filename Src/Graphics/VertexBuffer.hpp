#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer();
		VertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		~VertexBuffer();
		void BufferData(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		void BufferData(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		void Dispose();
		const unsigned int GetPointSize() const;
	private:
		unsigned int _point_size = 0;
	};
}