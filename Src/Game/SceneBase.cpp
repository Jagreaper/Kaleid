#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "App.hpp"

using namespace Kaleid::Game;

SceneBase::SceneBase(App*& app)
{
	this->_app = app;
	this->_renderer = app->GetRenderer();
	this->_graphics_factory = app->GetGraphicsFactory();
}