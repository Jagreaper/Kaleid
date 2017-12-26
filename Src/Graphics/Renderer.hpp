#pragma once

#include "stdafx.hpp"
#include "Material.hpp"
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
		void SetWireframeMode(bool enabled);
		void BindTexture(TextureBase* tex, int level = 0);
		void BindTextures(std::vector<TextureBase*>& textures);
		void BindTextures(std::vector<TextureBase*>* textures);
		void RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>& textures, std::function<void(ShaderProgram*&)> arguments);
		void RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>* textures, std::function<void(ShaderProgram*&)> arguments);
		void RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, Material* material, std::function<void(ShaderProgram*&, Material*)> arguments);
	private:
#ifdef DEBUG
		void ErrorCheck();
#endif
		bool _use_defaults, _is_loaded;
	};
}
API_END