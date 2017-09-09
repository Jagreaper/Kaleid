#pragma once

#include "stdafx.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Game
{
	class SceneBase;

	class KALEID_GAME_API App sealed
	{
	public:
		void Load();
		void Dispose();
		void Run();

		void SetRenderer(Kaleid::Graphics::Renderer*& renderer);
		Kaleid::Graphics::Renderer* GetRenderer();

		void SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory();

		void SetScene(SceneBase*& current_scene);
		SceneBase* GetScene();
	private:
		SceneBase* _current_scene = NULL;
		Kaleid::Graphics::Renderer* _renderer = NULL;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory = NULL;
		Kaleid::Graphics::Window* _window = NULL;
	};
}