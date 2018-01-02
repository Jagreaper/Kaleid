#pragma once

#include "Kaleid.Shared\Common.hpp"
#include "Kaleid.Game\SceneBase.hpp"
#include "RootScene.hpp"
#include "TestScene.hpp"

namespace Kaleid::Application
{
	class SceneManager sealed
	{
	public:
		static TestScene* CreateTestScene(Kaleid::Game::App* app);
		static RootScene* CreateRootScene(Kaleid::Game::App* app);
		static void FreeScene(Kaleid::Game::SceneBase* scenebase);
	};
}