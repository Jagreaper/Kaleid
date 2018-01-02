#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Model.hpp"
#include "Jagerts.Kaleid.Math\Transform.hpp"
#include <functional>

namespace Jagerts::Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class Renderer;
	class GraphicsFactory;
}

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API Cube : public Jagerts::Kaleid::Math::TransformableObject
	{
	public:
		Cube();

		void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&)> arguments);

		void SetShaderProgram(Jagerts::Kaleid::Graphics::ShaderProgram*& shader_program);
		Jagerts::Kaleid::Graphics::ShaderProgram* GetShaderProgram();

		static bool MeshExists();
		static Jagerts::Kaleid::Graphics::Mesh* CreateMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		static Jagerts::Kaleid::Graphics::Mesh* GetMesh();
		static void FreeMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory);
	private:
		Jagerts::Kaleid::Graphics::ShaderProgram* _shader_program;

		static bool _mesh_exists;
		static Jagerts::Kaleid::Graphics::Mesh* _mesh;
	};
}