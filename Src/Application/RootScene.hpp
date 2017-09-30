#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"
#include "Model.hpp"
#include "Cube.hpp"
#include "PerspectiveCamera.hpp"

class RootScene : public Kaleid::Game::SceneBase
{
public:
	RootScene(Kaleid::Game::App* app);
	void Load();
	void Update();
	void Render();
	void Dispose();
private:
	Kaleid::Graphics::ShaderProgram* _shader_program;
	Kaleid::Game::Model _model;
	Kaleid::Math::PerspectiveCamera _camera;
	Cube _cube;
};