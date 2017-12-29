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
	this->_mouse.Poll(window);
}

void SceneBase::Load()
{
	this->_o_time = clock();
}

void SceneBase::Update()
{
	this->_n_time = clock();
	this->_delta_time = (double)(this->_n_time - this->_o_time) / CLOCKS_PER_SEC;
	this->_o_time = this->_n_time;
}


const double& SceneBase::GetDeltaTime() const
{
	return this->_delta_time;
}