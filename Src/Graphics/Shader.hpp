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

	class GraphicsFactory;
	class ShaderProgram;

	class Shader sealed
	{
		friend class GraphicsFactory;
		friend class ShaderProgram;
	public:
		KALEID_GRAPHICS_API void SetSource(const char** source);
		KALEID_GRAPHICS_API void Compile();
	private:
		Shader(const ShaderType type);
		void Dispose();
		void Validate();
		const unsigned int GetId() const;

		unsigned int _id;
	};
}
API_END