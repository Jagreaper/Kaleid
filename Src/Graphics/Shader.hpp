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

	class KALEID_GRAPHICS_API Shader sealed
	{
	public:
		void SetSource(const char** source);
		void Compile();
	private:
		Shader(const ShaderType type);
		void Dispose();
		void Validate();

		unsigned int _id;

		friend class GraphicsFactory;
		friend class ShaderProgram;
	};
}
API_END