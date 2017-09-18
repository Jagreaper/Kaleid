#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "RootScene.hpp"

class SceneManager sealed
{
public:
	static RootScene* CreateRootScene(Kaleid::Game::App* app);
	static void FreeScene(Kaleid::Game::SceneBase* scenebase);
};