#include "stdafx.hpp"
#include "App.hpp"
#include "SceneBase.hpp"

using namespace Kaleid::Game;

void App::Run()
{
	// TODO: Implemented Run Code
}

void App::SetRenderer(Kaleid::Graphics::Renderer*& renderer)
{
	this->_renderer = renderer;
}

Kaleid::Graphics::Renderer* App::GetRenderer()
{
	return this->_renderer;
}

void App::SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory*& graphics_factory)
{
	this->_graphics_factory = graphics_factory;
}

Kaleid::Graphics::GraphicsFactory* App::GetGraphicsFactory()
{
	return this->_graphics_factory;
}

void App::SetScene(SceneBase*& current_scene)
{
	if (this->_current_scene != NULL)
	{
		this->_current_scene->dispose();
		delete this->_current_scene;
	}

	this->_current_scene = current_scene;

	if (this->_current_scene != NULL)
		this->_current_scene->load();
}

SceneBase* App::GetScene()
{
	return this->_current_scene;
}