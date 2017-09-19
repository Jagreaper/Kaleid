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

	class KALEID_GAME_API App sealed
	{
	public:
		App();
		void Load();
		void Dispose();
		void Run();
		void Close();

		void SetRenderer(Kaleid::Graphics::Renderer* renderer);
		Kaleid::Graphics::Renderer* GetRenderer();

		void SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory* graphics_factory);
		Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory();

		void SetScene(SceneBase* current_scene, std::function<void()> disposal);
		SceneBase* GetScene();

		std::vector<Kaleid::Graphics::Window*>* GetWindows();
		Kaleid::Graphics::Window* GetWindow(int index);
		bool IsRunning();
	private:
		SceneBase* _current_scene;
		std::function<void()> _disposal;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;

		std::vector<Kaleid::Graphics::Window*> _windows;

		bool _is_running;
	};
}
API_END