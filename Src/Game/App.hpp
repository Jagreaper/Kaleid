#pragma once

#include "stdafx.hpp"
#include "Renderer.hpp"
#include "GraphicsFactory.hpp"

namespace Kaleid::Game
{
	class SceneBase;

	class KALEID_GAME_API App sealed
	{
	public:
		void SetRenderer(Kaleid::Graphics::Renderer*& renderer);
		Kaleid::Graphics::Renderer* GetRenderer();

		void SetGraphicsFactory(Kaleid::Graphics::GraphicsFactory*& graphics_factory);
		Kaleid::Graphics::GraphicsFactory* GetGraphicsFactory();

		void SetScene(SceneBase*& current_scene);
		SceneBase* GetScene();
	private:
		SceneBase* _current_scene;
		Kaleid::Graphics::Renderer* _renderer;
		Kaleid::Graphics::GraphicsFactory* _graphics_factory;
	};
}