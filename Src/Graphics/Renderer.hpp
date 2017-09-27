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
		Renderer(bool use_defaults = true);
		void Load();
		bool IsLoaded();

		void Clear(float red, float green, float blue, float alpha);
		void SetViewport(float x, float y, float width, float height);
		void BindTextures(std::vector<TextureBase*>& textures);
		void RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>& textures, std::function<void()> arguments);
	private:
		bool _use_defaults, _is_loaded;
	};
}
API_END