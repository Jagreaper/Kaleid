#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class VertexBuffer : public BufferBase
	{
	public:
#ifdef KALEID_GRAPHICS_DLL
		VertexBuffer();
		VertexBuffer(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		VertexBuffer(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		~VertexBuffer();
#endif
		KALEID_GRAPHICS_API void BufferData(const float* data, size_t count, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		KALEID_GRAPHICS_API void BufferData(const std::vector<float>* data, unsigned int point_size, BufferUsage usage = BufferUsage::StaticDraw);
		KALEID_GRAPHICS_API void Dispose();
		KALEID_GRAPHICS_API const unsigned int GetPointSize() const;
#ifdef KALEID_GRAPHICS_DLL
	private:
		unsigned int _point_size;
#endif
	};
}
API_END