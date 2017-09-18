#include "stdafx.hpp"
#include "RootScene.hpp"

using namespace Kaleid::Game;

RootScene::RootScene(App* app)
	: SceneBase(app)
{
	// Skip
}

void RootScene::Load()
{
	this->_app->GetWindow(0)->MakeCurrent();
}

void RootScene::Update()
{
	// Skip
}

void RootScene::Render()
{
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

	this->_app->GetWindow(0)->SwapBuffers();
}

void RootScene::Dispose()
{
	// Skip
}