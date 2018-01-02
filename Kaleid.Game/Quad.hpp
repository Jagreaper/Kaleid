#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Model.hpp"
#include "Kaleid.Math\Transform.hpp"
#include <functional>

namespace Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class Renderer;
	class GraphicsFactory;
}

namespace Kaleid::Game
{
	class KALEID_GAME_API Quad : public Kaleid::Math::TransformableObject
	{
	public:
		Quad();

		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&)> arguments);

		void SetShaderProgram(Kaleid::Graphics::ShaderProgram*& shader_program);
		Kaleid::Graphics::ShaderProgram* GetShaderProgram();

		static bool MeshExists();
		static Kaleid::Graphics::Mesh* CreateMesh(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		static Kaleid::Graphics::Mesh* GetMesh();
		static void FreeMesh(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
	private:
		Kaleid::Graphics::ShaderProgram* _shader_program;

		static Kaleid::Graphics::Mesh* _mesh;
	};
}