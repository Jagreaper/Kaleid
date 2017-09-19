#include "stdafx.hpp"
#include "RootScene.hpp"
#include "ObjStreamDecoder.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <fstream>

using namespace Kaleid::Game;
using namespace Kaleid::IO;

RootScene::RootScene(App* app)
	: SceneBase(app)
{
	// Skip
}

void RootScene::Load()
{
	this->_app->GetWindow(0)->MakeCurrent();

	const char* path = "Models\\Parking Lot\\parking lot.obj";
	std::ifstream obj_stream;
	obj_stream.open(path);

	ObjStreamDecoder decoder;
	decoder.TryDecode(obj_stream, NULL, NULL);
	obj_stream.close();
}

void RootScene::Update()
{
	// Skip
}

void RootScene::Render()
{
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

	// Render Stuff

	this->_app->GetWindow(0)->SwapBuffers();
}

void RootScene::Dispose()
{
	// Skip
}