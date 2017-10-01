#pragma once

#include "stdafx.hpp"
#include "Keyboard.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class Renderer;
	class GraphicsFactory;
}

namespace Kaleid::Game
{
	class App;

	class KALEID_GAME_API SceneBase abstract
	{
	public:
		SceneBase(App*& app);
		virtual void Load() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Dispose() = 0;
		virtual void Poll(Kaleid::Graphics::Window*& window);
	protected:
		App* _app;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
		Kaleid::Input::Keyboard _keyboard;
	};
}
API_END