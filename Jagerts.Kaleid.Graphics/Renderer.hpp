#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Material.hpp"
#include <vector>
#include <functional>

#define jkgRenderableObject \
void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material* material)> arguments) \

#define jkgRenderableObjectVirtual \
virtual void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material* material)> arguments) \

#define jkgRenderableObjectSource(CLASS) \
void CLASS::Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material* material)> arguments) \

namespace Jagerts::Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class TextureBase;

	class JAGERTS_KALEID_GRAPHICS_API Renderer sealed
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

	class RenderableObject
	{
	public:
		jkgRenderableObjectVirtual = 0;
	};
}