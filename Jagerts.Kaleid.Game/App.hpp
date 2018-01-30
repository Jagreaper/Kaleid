#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include <vector>
#include <functional>

namespace Jagerts::Kaleid::Graphics
{
	class Window;
	class GraphicsFactory;
	class Renderer;
}

namespace Jagerts::Kaleid::Game
{
	class SceneBase;

	class JAGERTS_KALEID_GAME_API App
	{
	public:
		App();
		void Load();
		void Dispose();
		void Run();
		void Close();

		void SetRenderer(Jagerts::Kaleid::Graphics::Renderer* renderer);
		Jagerts::Kaleid::Graphics::Renderer* GetRenderer() const;

		void SetGraphicsFactory(Jagerts::Kaleid::Graphics::GraphicsFactory* graphics_factory);
		Jagerts::Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory() const;

		void SetScene(SceneBase* current_scene, std::function<void()> disposal);
		SceneBase* GetScene() const;

		const std::vector<Jagerts::Kaleid::Graphics::Window*>* GetWindows();
		Jagerts::Kaleid::Graphics::Window* GetWindow(int index) const;
		Jagerts::Kaleid::Graphics::Window* GetMainWindow() const;
		bool IsRunning();
	private:
		SceneBase* _current_scene;
		std::function<void()> _disposal;
		Jagerts::Kaleid::Graphics::Renderer* _renderer;
		Jagerts::Kaleid::Graphics::GraphicsFactory* _graphics_factory;

		std::vector<Jagerts::Kaleid::Graphics::Window*> _windows;

		bool _is_running;
	};
}