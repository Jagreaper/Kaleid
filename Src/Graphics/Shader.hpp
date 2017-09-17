#pragma once

#include "stdafx.hpp"

API_BEGIN
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
		KALEID_GRAPHICS_API void SetSource(const char** source);
		KALEID_GRAPHICS_API void Compile();
		KALEID_GRAPHICS_API void Dispose();
		KALEID_GRAPHICS_API const unsigned int GetId() const;
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
API_END