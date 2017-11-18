#include "stdafx.hpp"
#include "SceneManager.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Application;

RootScene* SceneManager::CreateRootScene(App* app)
{
	return new RootScene(app);
}

TestScene* SceneManager::CreateTestScene(App* app)
{
	return new TestScene(app);
}

void SceneManager::FreeScene(SceneBase* scenebase)
{
	scenebase->Dispose();
	delete scenebase;
}