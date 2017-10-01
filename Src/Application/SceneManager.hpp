#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "RootScene.hpp"
#include "TestScene.hpp"

class SceneManager sealed
{
public:
	static TestScene* CreateTestScene(Kaleid::Game::App* app);
	static RootScene* CreateRootScene(Kaleid::Game::App* app);
	static void FreeScene(Kaleid::Game::SceneBase* scenebase);
};