#pragma once

#include "stdafx.hpp"

namespace polarious::graphics
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
		Shader(const char** source, const ShaderType type);
		~Shader();
		void Dispose();
		const unsigned int GetId() const;
	private:
		void Validate();
		unsigned int _id;
	};
}