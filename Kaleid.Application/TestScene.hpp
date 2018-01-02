#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Kaleid.Game\SceneBase.hpp"
#include "Kaleid.Game\Model.hpp"
#include "Kaleid.Game\Cube.hpp"
#include "Kaleid.Math\PerspectiveCamera.hpp"
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
		Kaleid::Game::Cube _cube;
	};
}