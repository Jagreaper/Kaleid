#pragma once

#include "stdafx.hpp"
#include "BufferBase.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class IndexBuffer : public BufferBase
	{
	public:
		KALEID_GRAPHICS_API void BufferData(const unsigned int* data, size_t count, BufferUsage usage = BufferUsage::StaticDraw);
		KALEID_GRAPHICS_API void BufferData(const std::vector<unsigned int>* data, BufferUsage usage = BufferUsage::StaticDraw);
#ifdef KALEID_GRAPHICS_DLL
		void Bind();

		IndexBuffer();
#endif
	};
}
API_END