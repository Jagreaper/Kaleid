#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "Model.hpp"
#include "Cube.hpp"
#include "PerspectiveCamera.hpp"
#include <time.h>

namespace Kaleid::Application
{
	class TestScene : public Kaleid::Game::SceneBase
	{
	public:
		TestScene(Kaleid::Game::App* app);
		void Load();
		void Update();
		void Render();
		void Dispose();
	private:
		void BuildShaderProgram();
		void BuildMesh();
		void CreateKeyboardBindings();

		Kaleid::Math::PerspectiveCamera _camera;
		Cube _cube;
	};
}