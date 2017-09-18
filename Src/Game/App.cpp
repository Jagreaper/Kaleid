#include "stdafx.hpp"
#include "App.hpp"
#include "SceneBase.hpp"
#include "RootScene.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Graphics;

App::App()
{
	this->_current_scene = NULL;
	this->_renderer = NULL;
	this->_graphics_factory = NULL;
	this->_is_running = false;
	this->_windows = new std::vector<Window*>();
}

void App::Load()
{
	Window* window = this->_graphics_factory->CreateWindow(800, 600, "OpenGL Window");
	this->_windows->push_back(window);

	this->SetScene(new RootScene(this));
}

void App::Dispose()
{
	if (this->_current_scene != NULL)
	{
		this->_current_scene->Dispose();
		delete this->_current_scene;
	}

	for (int index = 0; index < this->_windows->size(); index++)
	{
		Window* window = this->GetWindow(index);
		this->_graphics_factory->FreeWindow(window);
		delete window;
	}

	this->_windows->clear();
}

void App::Run()
{
	this->_is_running = true;

	while (this->_is_running) // Main Loop
	{
		Window::PollEvents();

		if (this->_current_scene != NULL)
		{
			this->_current_scene->Update();
			this->_current_scene->Render();
		}
	}
}

void App::Close()
{
	this->_is_running = false;
}

void App::SetRenderer(Kaleid::Graphics::Renderer* renderer)
{
	this->_renderer = renderer;
}

Renderer* App::GetRenderer()
{
	return this->_renderer;
}

void App::SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory* graphics_factory)
{
	this->_graphics_factory = graphics_factory;
}

GraphicsFactory* App::GetGraphicsFactory()
{
	return this->_graphics_factory;
}

void App::SetScene(SceneBase* current_scene)
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

std::vector<Kaleid::Graphics::Window*>* App::GetWindows()
{
	return this->_windows;
}

Kaleid::Graphics::Window* App::GetWindow(int index)
{
	return this->_windows->at(index);
}

bool App::IsRunning()
{
	return this->_is_running;
}