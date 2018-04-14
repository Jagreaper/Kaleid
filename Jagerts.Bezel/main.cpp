#include <iostream>
#include "Jagerts.Kaleid.Game/App.hpp"
#include "Jagerts.Kaleid.Graphics/GraphicsFactory.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"
#include "RootScene.hpp"
#include "SceneManager.hpp"

using namespace Jagerts::Kaleid::Game;
using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Bezel;

int main()
{
	App app;

	GraphicsFactory graphicsFactory;
	Renderer renderer;
	app.SetGraphicsFactory(&graphicsFactory);
	app.SetRenderer(&renderer);
	app.SetScene(SceneManager::CreateRootScene(&app), std::bind(SceneManager::FreeScene, app.GetScene()));

	app.Load();
	app.Run();
	app.Dispose();

	return EXIT_SUCCESS;
}