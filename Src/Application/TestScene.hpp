#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "Model.hpp"
#include "Cube.hpp"
#include "PerspectiveCamera.hpp"
#include <time.h>

namespace Kaleid::Application
{
	class TestScene : public Kaleid::Game::SceneBase
	{
	public:
		TestScene(Kaleid::Game::App* app);
		void Load();
		void Update();
		void Render();
		void Dispose();
		double GetDeltaTime();
	private:
		void BuildShaderProgram();
		void BuildMesh();
		void CreateKeyboardBindings();

		Kaleid::Math::PerspectiveCamera _camera;
		Cube _cube;

		clock_t _o_time;
		clock_t _n_time;
		double _delta_time;
	};
}