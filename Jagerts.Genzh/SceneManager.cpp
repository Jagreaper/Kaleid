#include "SceneManager.hpp"

using namespace Jagerts::Kaleid::Game;
using namespace Jagerts::Genzh;

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