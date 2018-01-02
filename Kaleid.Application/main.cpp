#include <iostream>
#include "Kaleid.Game\App.hpp"
#include "Kaleid.Graphics\GraphicsFactory.hpp"
#include "Kaleid.Graphics\Renderer.hpp"
#include "RootScene.hpp"
#include "SceneManager.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::Application;

#ifdef DEBUG
int main()
#endif
#ifdef RELEASE
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#endif
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