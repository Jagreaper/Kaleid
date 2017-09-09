#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class IndexBuffer : public BufferBase
	{
	public:
#ifdef KALEID_GRAPHICS_DLL
		IndexBuffer();
		IndexBuffer(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer(const std::vector<unsigned int>* data, BufferUsage usage = BufferUsage::StaticDraw);
		~IndexBuffer();
#endif
		void KALEID_GRAPHICS_API BufferData(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);
		void KALEID_GRAPHICS_API BufferData(const std::vector<unsigned int>* data, BufferUsage usage = BufferUsage::StaticDraw);
		void KALEID_GRAPHICS_API Dispose();
	};
}