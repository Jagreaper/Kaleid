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
	// Skip
}

void RootScene::Update()
{
	// Skip
}

void RootScene::Render()
{
	this->_renderer->Clear(1.0f, 0.0f, 0.0f, 1.0f);

	this->_app->GetWindow()->SwapBuffers();
}

void RootScene::Dispose()
{
	// Skip
}