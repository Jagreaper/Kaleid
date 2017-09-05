#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API IndexBuffer : public BufferBase
	{
	public:
		IndexBuffer();
		IndexBuffer(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);
		IndexBuffer(const std::vector<unsigned int>* data, BufferUsage usage = BufferUsage::StaticDraw);
		~IndexBuffer();
		void BufferData(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);
		void BufferData(const std::vector<unsigned int>* data, BufferUsage usage = BufferUsage::StaticDraw);
		void Dispose();
	private:
	};
}