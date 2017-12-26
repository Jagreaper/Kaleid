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
		void SetMaterial(const Kaleid::Graphics::Material material);
		const Kaleid::Graphics::Material& GetMaterial() const;
		void SetMaterialInfo(const Kaleid::Graphics::MaterialInfo material);
		const Kaleid::Graphics::MaterialInfo& GetMaterialInfo() const;
		void SetShaderProgram(Kaleid::Graphics::ShaderProgram*& shader_program);
		const Kaleid::Graphics::ShaderProgram* GetShaderProgram() const;
		Kaleid::Graphics::ShaderProgram*& GetShaderProgram();
		Kaleid::Math::Transform* GetTransform();
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&, Kaleid::Graphics::Material*)> arguments);
		void SetName(const std::string name);
		void SetName(const char* name);
		const std::string& GetName() const;
	private:
		std::string _name;
		Kaleid::Graphics::Mesh* _mesh;
		Kaleid::Graphics::Material _material;
		Kaleid::Graphics::MaterialInfo _material_info;
		Kaleid::Graphics::ShaderProgram* _shader_program;
		Kaleid::Math::Transform _transform;
	};
}
API_END