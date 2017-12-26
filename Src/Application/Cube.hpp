#pragma once

#include "stdafx.hpp"
#include "Model.hpp"
#include "Transform.hpp"
#include <functional>

namespace Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class Renderer;
	class GraphicsFactory;
}

namespace Kaleid::Application
{
	class Cube
	{
	public:
		Cube();

		void Render(Kaleid::Graphics::Renderer*& renderer, std::function<void(Kaleid::Graphics::ShaderProgram*&)> arguments);

		void SetShaderProgram(Kaleid::Graphics::ShaderProgram*& shader_program);
		Kaleid::Graphics::ShaderProgram* GetShaderProgram();
		Kaleid::Math::Transform* GetTransform();

		static void Load(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		static void Dispose(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
	private:
		Kaleid::Graphics::ShaderProgram* _shader_program;
		Kaleid::Math::Transform _transform;

		static Kaleid::Graphics::Mesh* _mesh;
	};
}