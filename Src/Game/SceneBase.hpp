#pragma once

#include "stdafx.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Game
{
	class SceneBase abstract
	{
	public:
		SceneBase(App*& app);
		virtual void load() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void dispose() = 0;
	protected:
		App* _app;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
	};
}