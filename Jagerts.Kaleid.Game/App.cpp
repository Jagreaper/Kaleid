#include "App.hpp"
#include "SceneBase.hpp"
#include "Jagerts.Kaleid.Graphics/Window.hpp"
#include "Jagerts.Kaleid.Graphics/GraphicsFactory.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"

using namespace Jagerts::Kaleid::Game;
using namespace Jagerts::Kaleid::Graphics;

App::App()
{
	this->_current_scene = NULL;
	this->_disposal = NULL;
	this->_renderer = NULL;
	this->_graphics_factory = NULL;
	this->_is_running = false;
}

void App::Load()
{
	Window* window = this->_graphics_factory->CreateWindow(1280, 720, "OpenGL Window");
	this->_windows.push_back(window);
}

void App::Dispose()
{
	if (this->_current_scene != NULL)
	{
		this->_current_scene->Dispose();
		delete this->_current_scene;
	}

	for (unsigned int index = 0; index < (unsigned int)this->_windows.size(); index++)
	{
		Window* window = this->GetWindow(index);
		this->_graphics_factory->FreeWindow(window);
	}

	this->_windows.clear();
}

void App::Run()
{
	this->_renderer->Load();

	if (this->_current_scene != NULL)
		this->_current_scene->Load();

	this->_is_running = true;

	while (this->_is_running) // Main Loop
	{
		Window::PollEvents();

		if (this->_current_scene != NULL)
		{
			for (unsigned int index = 0; index < this->_windows.size(); index++)
				this->_current_scene->Poll(this->_windows[index]);

			this->_current_scene->Update();
			this->_current_scene->Render();
		}
	}
}

void App::Close()
{
	this->_is_running = false;
}

void App::SetRenderer(Jagerts::Kaleid::Graphics::Renderer* renderer)
{
	this->_renderer = renderer;
}

Renderer* App::GetRenderer() const
{
	return this->_renderer;
}

void App::SetGraphicsFactory(Jagerts::Kaleid::Graphics::GraphicsFactory* graphics_factory)
{
	this->_graphics_factory = graphics_factory;
}

GraphicsFactory* App::GetGraphicsFactory() const
{
	return this->_graphics_factory;
}

void App::SetScene(SceneBase* current_scene, std::function<void()> disposal)
{
	if (this->_current_scene != NULL)
	{
		if (this->_disposal != NULL)
			this->_disposal;
		else
		{
			this->_current_scene->Dispose();
			delete this->_current_scene;
		}
	}

	this->_current_scene = current_scene;
	this->_disposal = disposal;

	if (this->IsRunning() && this->_current_scene != NULL)
		this->_current_scene->Load();
}

SceneBase* App::GetScene() const
{
	return this->_current_scene;
}

const std::vector<Window*>* App::GetWindows()
{
	return &this->_windows;
}

Window* App::GetWindow(int index) const
{
	return this->_windows[index];
}

Window* App::GetMainWindow() const
{
	return this->_windows[0];
}

bool App::IsRunning()
{
	return this->_is_running;
}