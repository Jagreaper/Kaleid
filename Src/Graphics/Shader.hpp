#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	enum ShaderType
	{
		Fragment = 0x8B30,
		Vertex = 0x8B31,
		Geometry = 0x8DD9,
		Compute = 0x91B9,
	};

	class Shader
	{
	public:
		KALEID_GRAPHICS_API void SetSource(const char** source);
		KALEID_GRAPHICS_API void Compile();
#ifdef KALEID_GRAPHICS_DLL
		Shader(const ShaderType type);

		void Dispose();
		const unsigned int GetId() const;
	private:
		void Validate();
		unsigned int _id;
#endif
	};
}
API_END