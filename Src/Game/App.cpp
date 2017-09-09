#include "stdafx.hpp"
#include "App.hpp"
#include "SceneBase.hpp"

using namespace Kaleid::Game;

void App::Load()
{
	this->_window = this->_graphics_factory->CreateWindow(800, 600, "OpenGL Window");
	this->_window->MakeCurrent();
}

void App::Dispose()
{
	if (this->_current_scene != NULL)
	{
		this->_current_scene->Dispose();
		delete this->_current_scene;
	}

	this->_graphics_factory->FreeWindow(this->_window);
}

void App::Run()
{
	while (this->_window->Exists()) // Main Loop
	{
		this->_window->PollEvents();

		if (this->_current_scene != NULL)
		{
			this->_current_scene->Update();
			this->_current_scene->Render();
		}
	}
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
		this->_current_scene->Dispose();
		delete this->_current_scene;
	}

	this->_current_scene = current_scene;

	if (this->_current_scene != NULL)
		this->_current_scene->Load();
}

SceneBase* App::GetScene()
{
	return this->_current_scene;
}