#pragma once

#include "stdafx.hpp"
#include <vector>
#include <functional>

API_BEGIN
namespace Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class TextureBase;

	class KALEID_GRAPHICS_API Renderer sealed
	{
	public:
		Renderer();
		void Load();
		void Dispose();

		void Clear(float red, float green, float blue, float alpha);
		void BindTextures(std::vector<TextureBase*>& textures);
		void RenderMesh(Mesh*& mesh, ShaderProgram*& shader, std::vector<TextureBase*>& textures, std::function<void()> arguments);
	};
}
API_END