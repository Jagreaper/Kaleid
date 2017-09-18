#pragma once

#include "stdafx.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "GraphicsFactory.hpp"
#include <vector>
#include <functional>

API_BEGIN
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
		KALEID_GAME_API void Close();

		KALEID_GAME_API void SetRenderer(Kaleid::Graphics::Renderer* renderer);
		KALEID_GAME_API Kaleid::Graphics::Renderer* GetRenderer();

		KALEID_GAME_API void SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory* graphics_factory);
		KALEID_GAME_API Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory();

		KALEID_GAME_API void SetScene(SceneBase* current_scene, std::function<void()> disposal);
		KALEID_GAME_API SceneBase* GetScene();

		KALEID_GAME_API std::vector<Kaleid::Graphics::Window*>* GetWindows();
		KALEID_GAME_API Kaleid::Graphics::Window* GetWindow(int index);
		KALEID_GAME_API bool IsRunning();
	private:
		SceneBase* _current_scene;
		std::function<void()> _disposal;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;

		std::vector<Kaleid::Graphics::Window*>* _windows;

		bool _is_running;
	};
}
API_END