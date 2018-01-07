#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Game\SceneBase.hpp"
#include "Jagerts.Kaleid.Game\Model.hpp"
#include "Jagerts.Kaleid.Game\Cube.hpp"
#include "Jagerts.Kaleid.Math\PerspectiveCamera.hpp"
#include <time.h>

namespace Jagerts::Kaleid::Application
{
	class TestScene : public Jagerts::Kaleid::Game::SceneBase
	{
	public:
		TestScene(Jagerts::Kaleid::Game::App* app);
		jkgImplementSceneBase;
	private:
		void BuildShaderProgram();
		void BuildMesh();
		void CreateKeyboardBindings();

		Jagerts::Kaleid::Math::PerspectiveCamera _camera;
		Jagerts::Kaleid::Game::Cube _cube;
	};
}