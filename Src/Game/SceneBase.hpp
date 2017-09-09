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
		virtual void Load() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Dispose() = 0;
	protected:
		App* _app;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
	};
}