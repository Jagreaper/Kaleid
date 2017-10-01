#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "App.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Graphics;

SceneBase::SceneBase(App*& app)
{
	this->_app = app;
	this->_renderer = app->GetRenderer();
	this->_graphics_factory = app->GetGraphicsFactory();
}

void SceneBase::Poll(Window*& window)
{
	this->_keyboard.Poll(window);
}