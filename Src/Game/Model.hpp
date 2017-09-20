#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class Mesh;
	class TextureBase;
	class ShaderProgram;
	class Renderer;
}

namespace Kaleid::Game
{
	class KALEID_GAME_API Model sealed
	{
	public:
		void SetMesh(Kaleid::Graphics::Mesh*& mesh);
		Kaleid::Graphics::Mesh* GetMesh();
		void SetTextures(std::vector<Kaleid::Graphics::TextureBase*>& textures);
		std::vector<Kaleid::Graphics::TextureBase*>* GetTextures();
		void SetShaderProgram(Kaleid::Graphics::ShaderProgram*& shader_program);
		Kaleid::Graphics::ShaderProgram* GetShaderProgram();
		Kaleid::Math::Transform* GetTransform();
		void Render(Kaleid::Graphics::Renderer*& renderer);
	private:
		Kaleid::Graphics::Mesh* _mesh;
		std::vector<Kaleid::Graphics::TextureBase*> _textures;
		Kaleid::Graphics::ShaderProgram* _shader_program;
		Kaleid::Math::Transform _transform;
	};
}
API_END