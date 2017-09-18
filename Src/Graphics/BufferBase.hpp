#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	enum KALEID_GRAPHICS_API BufferUsage
	{
		StreamDraw = 0x88E0,
		StreamRead = 0x88E1,
		StreamCopy = 0x88E2,
		StaticDraw = 0x88E4,
		StaticRead = 0x88E5,
		StaticCopy = 0x88E6,
		DynamicDraw = 0x88E8,
		DynamicRead = 0x88E9,
		DynamicCopy = 0x88EA,
	};

	class BufferBase abstract
	{
	public:
		KALEID_GRAPHICS_API const size_t GetLength() const;
		KALEID_GRAPHICS_API const bool Exists() const;
#ifdef KALEID_GRAPHICS_DLL
		BufferBase();

		virtual void Bind() = 0;

		void Dispose();
		const unsigned int GetId() const;
		const int GetTypeInfo() const;
	protected:
		unsigned int _id;
		size_t _length;
		int _type_info;
#endif
	};
}
API_END