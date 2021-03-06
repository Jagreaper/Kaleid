#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"

namespace Jagerts::Kaleid::Graphics
{
	enum class BufferUsage : unsigned int
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

	class Mesh;

	class JAGERTS_KALEID_GRAPHICS_API BufferBase
	{
	public:
		const size_t GetLength() const;
		const bool Exists() const;
	protected:
		BufferBase();
		unsigned int _id;
		size_t _length;
		int _type_info;
		virtual void Bind() = 0;
		void Dispose();

		friend class Mesh;
	};
}