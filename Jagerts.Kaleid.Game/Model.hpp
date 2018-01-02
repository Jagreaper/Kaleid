#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Math\Transform.hpp"
#include "ModelComponent.hpp"
#include "Jagerts.Kaleid.Graphics\Material.hpp"
#include "Jagerts.Kaleid.Graphics\Renderer.hpp"
#include <functional>
#include <vector>

namespace Jagerts::Kaleid::Graphics
{
	class Mesh;
	class TextureBase;
	class ShaderProgram;
}

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API Model sealed : public Jagerts::Kaleid::Math::TransformableObject, public Jagerts::Kaleid::Graphics::RenderableObject
	{
	public:
		static Model* AllocateMemory();
		static void FreeMemory(Model*& model);
		static void FreeAllMemory();
		void AddComponent(ModelComponent* component);
		void AddComponents(std::vector<ModelComponent*>& components);
		void RemoveComponent(const std::string name);
		void RemoveComponent(int index);
		void RemoveComponents();
		const ModelComponent* GetComponent(const std::string name);
		const ModelComponent* GetComponent(int index);
		std::vector<ModelComponent*>* GetComponents();
		void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material* material)> arguments);
	protected:
		inline Model() { }
		static std::vector<Model*> _models;
		std::vector<ModelComponent*> _model_components;
	};

	class JAGERTS_KALEID_GAME_API ModelObject : public Jagerts::Kaleid::Math::TransformableObject, public Jagerts::Kaleid::Graphics::RenderableObject
	{
	public:
		void AddModel(const char* name, Model*& model);
		void RemoveModel(const char* name);
		void RemoveModels();
		virtual void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&, Jagerts::Kaleid::Graphics::Material* material)> arguments);
	protected:
		std::unordered_map<const char*, Model*> _models;
	};
}