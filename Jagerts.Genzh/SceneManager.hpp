#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Game/SceneBase.hpp"
#include "RootScene.hpp"
#include "TestScene.hpp"

namespace Jagerts::Genzh
{
	class SceneManager
	{
	public:
		static TestScene* CreateTestScene(Jagerts::Kaleid::Game::App* app);
		static RootScene* CreateRootScene(Jagerts::Kaleid::Game::App* app);
		static void FreeScene(Jagerts::Kaleid::Game::SceneBase* scenebase);
	};
}