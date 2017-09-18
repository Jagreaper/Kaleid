#pragma once

#include "stdafx.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include "GraphicsFactory.hpp"

API_BEGIN
namespace Kaleid::Game
{
	class SceneBase abstract
	{
	public:
		KALEID_GAME_API SceneBase(App*& app);
		KALEID_GAME_API virtual void Load() = 0;
		KALEID_GAME_API virtual void Update() = 0;
		KALEID_GAME_API virtual void Render() = 0;
		KALEID_GAME_API virtual void Dispose() = 0;
	protected:
		App* _app;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
	};
}
API_END