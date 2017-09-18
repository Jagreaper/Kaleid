#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"

class RootScene : public Kaleid::Game::SceneBase
{
public:
	RootScene(Kaleid::Game::App* app);
	void Load();
	void Update();
	void Render();
	void Dispose();
};