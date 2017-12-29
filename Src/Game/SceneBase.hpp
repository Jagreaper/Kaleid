#pragma once

#include "stdafx.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include <ctime>

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
		virtual void Render() = 0;
		virtual void Dispose() = 0;
		virtual void Poll(Kaleid::Graphics::Window*& window);
		virtual void Load();
		virtual void Update();
		const double& GetDeltaTime() const;
	protected:
		App* _app;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
		Kaleid::Input::Keyboard _keyboard;
		Kaleid::Input::Mouse _mouse;

		clock_t _o_time;
		clock_t _n_time;
		double _delta_time;
	};
}
API_END