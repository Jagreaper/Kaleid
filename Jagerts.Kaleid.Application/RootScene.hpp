#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Game\SceneBase.hpp"
#include "Jagerts.Kaleid.Game\Actor.hpp"
#include "Jagerts.Kaleid.Math\PerspectiveCamera.hpp"
#include <time.h>

namespace Jagerts::Kaleid::Application
{
	class RootScene : public Jagerts::Kaleid::Game::SceneBase
	{
	public:
		RootScene(Jagerts::Kaleid::Game::App* app);
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

		Jagerts::Kaleid::Graphics::ShaderProgram* _program;
		Jagerts::Kaleid::Game::Actor _actor;
		Jagerts::Kaleid::Math::PerspectiveCamera _camera;
	};
}