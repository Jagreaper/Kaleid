#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "Actor.hpp"
#include "PerspectiveCamera.hpp"
#include <time.h>

namespace Kaleid::Application
{
	class RootScene : public Kaleid::Game::SceneBase
	{
	public:
		RootScene(Kaleid::Game::App* app);
		void Load();
		void Update();
		void Render();
		void Dispose();
	private:
		void BuildShaderProgram();
		void BuildMesh();
		void CreateKeyboardBindings();
		void CameraMouseMovement(const double& x_delta, const double& y_delta);

		double _xpos_old;
		double _ypos_old;
		double _xpos_new;
		double _ypos_new;

		Kaleid::Graphics::ShaderProgram* _program;
		Kaleid::Game::Actor _actor;
		Kaleid::Math::PerspectiveCamera _camera;
	};
}