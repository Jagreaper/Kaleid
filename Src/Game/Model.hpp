#pragma once

#include "stdafx.hpp"
#include "Transform.hpp"
#include "ModelComponent.hpp"
#include "Material.hpp"
#include "Renderer.hpp"
#include <functional>
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class Mesh;
	class TextureBase;
	class ShaderProgram;
}

namespace Kaleid::Game
{
	class KALEID_GAME_API Model sealed : public Kaleid::Math::TransformableObject, public Kaleid::Graphics::RenderableObject
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
		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&, Kaleid::Graphics::Material* material)> arguments);
	protected:
		inline Model() { }
		static std::vector<Model*> _models;
		std::vector<ModelComponent*> _model_components;
	};

	class KALEID_GAME_API ModelObject : public Kaleid::Math::TransformableObject, public Kaleid::Graphics::RenderableObject
	{
	public:
		void AddModel(const char* name, Model*& model);
		void RemoveModel(const char* name);
		void RemoveModels();
		virtual void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&, Kaleid::Graphics::Material* material)> arguments);
	protected:
		std::unordered_map<const char*, Model*> _models;
	};
}
API_END