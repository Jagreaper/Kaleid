#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer();
		VertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		~VertexBuffer();
		void KALEID_GRAPHICS_API BufferData(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		void KALEID_GRAPHICS_API BufferData(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		void KALEID_GRAPHICS_API Dispose();
		const unsigned int KALEID_GRAPHICS_API GetPointSize() const;
	private:
		unsigned int _point_size = 0;
	};
}