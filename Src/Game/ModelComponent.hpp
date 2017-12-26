#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include <string>
#include <functional>
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
	class KALEID_GAME_API ModelComponent sealed
	{
	public:
		void SetMesh(Kaleid::Graphics::Mesh*& mesh);
		const Kaleid::Graphics::Mesh* GetMesh() const;
		Kaleid::Graphics::Mesh*& GetMesh();
		void SetMaterial(const Material material);
		const Kaleid::Game::Material& GetMaterial() const;
		void SetShaderProgram(Kaleid::Graphics::ShaderProgram*& shader_program);
		const Kaleid::Graphics::ShaderProgram* GetShaderProgram() const;
		Kaleid::Graphics::ShaderProgram*& GetShaderProgram();
		Kaleid::Math::Transform* GetTransform();
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&)> arguments);
		void SetName(const std::string name);
		void SetName(const char* name);
		const std::string& GetName() const;
	private:
		std::string _name;
		Kaleid::Graphics::Mesh* _mesh;
		Material _material;
		Kaleid::Graphics::ShaderProgram* _shader_program;
		Kaleid::Math::Transform _transform;
	};
}
API_END