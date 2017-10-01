#include "stdafx.hpp"
#include <iostream>
#include "App.hpp"
#include "GraphicsFactory.hpp"
#include "Renderer.hpp"
#include "RootScene.hpp"
#include "SceneManager.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Graphics;

int main()
{
	App app;

	GraphicsFactory graphicsFactory;
	Renderer renderer;
	app.SetGraphicsFactory(&graphicsFactory);
	app.SetRenderer(&renderer);
	app.SetScene(SceneManager::CreateTestScene(&app), std::bind(SceneManager::FreeScene, app.GetScene()));

	app.Load();
	app.Run();
	app.Dispose();

	return EXIT_SUCCESS;
}