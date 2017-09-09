#pragma once

#include "stdafx.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Game
{
	class SceneBase;

	class App sealed
	{
	public:
		KALEID_GAME_API App();
		KALEID_GAME_API void Load();
		KALEID_GAME_API void Dispose();
		KALEID_GAME_API void Run();

		KALEID_GAME_API void SetRenderer(Kaleid::Graphics::Renderer*& renderer);
		KALEID_GAME_API Kaleid::Graphics::Renderer* GetRenderer();

		KALEID_GAME_API void SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		KALEID_GAME_API Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory();

		KALEID_GAME_API void SetScene(SceneBase*& current_scene);
		KALEID_GAME_API SceneBase* GetScene();
#ifdef KALEID_GAME_DLL
	private:
		SceneBase* _current_scene = NULL;
		Kaleid::Graphics::Renderer* _renderer = NULL;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory = NULL;
		Kaleid::Graphics::Window* _window = NULL;
#endif
	};
}