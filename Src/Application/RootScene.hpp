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
		
		Kaleid::Graphics::ShaderProgram* _program;
		Kaleid::Game::Actor _actor;
		Kaleid::Math::PerspectiveCamera _camera;
	};
}