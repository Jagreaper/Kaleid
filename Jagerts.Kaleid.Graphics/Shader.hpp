#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"

namespace Jagerts::Kaleid::Graphics
{
	enum class ShaderType : int
	{
		Fragment = 0x8B30,
		Vertex = 0x8B31,
		Geometry = 0x8DD9,
		Compute = 0x91B9,
	};

	class GraphicsFactory;
	class ShaderProgram;

	class JAGERTS_KALEID_GRAPHICS_API Shader
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