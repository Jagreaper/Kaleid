#pragma once

#include "stdafx.hpp"

namespace Kaleid::Graphics
{
	enum KALEID_GRAPHICS_API ShaderType
	{
		Fragment = 0x8B30,
		Vertex = 0x8B31,
		Geometry = 0x8DD9,
		Compute = 0x91B9,
	};

	class Shader
	{
	public:
		void KALEID_GRAPHICS_API SetSource(const char** source);
		void KALEID_GRAPHICS_API Compile();
		void KALEID_GRAPHICS_API Dispose();
		const unsigned int KALEID_GRAPHICS_API GetId() const;
#ifdef KALEID_GRAPHICS_DLL
		Shader(const ShaderType type);
		Shader(const char** source, const ShaderType type);
		~Shader();

	private:
		void Validate();
		unsigned int _id;
#endif
	};
}