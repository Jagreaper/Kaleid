#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"
#include "Jagerts.Kaleid.Graphics/Material.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"
#include <string>
#include <functional>
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
}

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API ModelComponent sealed : public Jagerts::Kaleid::Math::TransformableObject, public Jagerts::Kaleid::Graphics::RenderableObject
	{
	public:
		static ModelComponent* AllocateMemory();
		static void FreeMemory(ModelComponent*& model_component);
		static void FreeAllMemory();
		void SetMesh(Jagerts::Kaleid::Graphics::Mesh*& mesh);
		const Jagerts::Kaleid::Graphics::Mesh* GetMesh() const;
		Jagerts::Kaleid::Graphics::Mesh*& GetMesh();
		void SetMaterial(const Jagerts::Kaleid::Graphics::Material material);
		Jagerts::Kaleid::Graphics::Material& GetMaterial();
		void SetMaterialInfo(const Jagerts::Kaleid::Graphics::MaterialInfo material);
		Jagerts::Kaleid::Graphics::MaterialInfo& GetMaterialInfo();
		void SetShaderProgram(Jagerts::Kaleid::Graphics::ShaderProgram*& shader_program);
		const Jagerts::Kaleid::Graphics::ShaderProgram* GetShaderProgram() const;
		Jagerts::Kaleid::Graphics::ShaderProgram*& GetShaderProgram();
		void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material*)> arguments);
		void SetName(const std::string name);
		void SetName(const char* name);
		const std::string& GetName() const;
		jkmUsingTransformableObject;
	private:
		inline ModelComponent() { }
		static std::vector<ModelComponent*> _model_components;
		std::string _name;
		Jagerts::Kaleid::Graphics::Mesh* _mesh;
		Jagerts::Kaleid::Graphics::Material _material;
		Jagerts::Kaleid::Graphics::MaterialInfo _material_info;
		Jagerts::Kaleid::Graphics::ShaderProgram* _shader_program;
	};
}