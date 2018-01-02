#include "TestScene.hpp"
#include "Jagerts.Kaleid.IO\ObjModelDecoder.hpp"
#include "Jagerts.Kaleid.Graphics\GraphicsFactory.hpp"
#include "Jagerts.Kaleid.Graphics\Shader.hpp"
#include "Jagerts.Kaleid.Graphics\ShaderProgram.hpp"
#include "Jagerts.Kaleid.Game\App.hpp"
#include "Jagerts.Kaleid.Graphics\Renderer.hpp"
#include "Jagerts.Kaleid.Graphics\Mesh.hpp"
#include "Jagerts.Kaleid.Graphics\Window.hpp"
#include "Jagerts.Kaleid.Math\Matrix.hpp"
#include "Jagerts.Kaleid.Input\Keyboard.hpp"
#include "Jagerts.Kaleid.Input\KeyBinding.hpp"
#include <iostream>
#include <fstream>

using namespace Jagerts::Kaleid::Math;
using namespace Jagerts::Kaleid::Game;
using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Kaleid::IO;
using namespace Jagerts::Kaleid::Input;
using namespace Jagerts::Kaleid::Application;

TestScene::TestScene(App* app)
	: SceneBase(app)
{
	// Skip
}

void TestScene::BuildShaderProgram()
{
	const char* vertex_source = R"(
	#version 410

	layout(location = 0) in vec3 vp;

	uniform mat4 mvp;
	varying vec3 col;

	void main()
	{
	    col = (vp + 1.0) / 2.0;
		gl_Position = mvp * vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	const char* fragment_source = R"(
	#version 410

	out vec4 frag_colour;

	uniform mat4 mvp;
	varying vec3 col;

	void main()
	{
		frag_colour = vec4(col.x, col.y, col.z, 1.0);
	}

	)";

	Shader* vertex_shader = this->_graphics_factory->CreateShader(&vertex_source, ShaderType::Vertex);
	Shader* fragment_shader = this->_graphics_factory->CreateShader(&fragment_source, ShaderType::Fragment);

	// Create Shader Program
	ShaderProgram* program = this->_graphics_factory->CreateShaderProgram();
	program->Attach(vertex_shader);
	program->Attach(fragment_shader);
	program->Link();
	program->Dettach(vertex_shader);
	program->Dettach(fragment_shader);

	// Clean Up
	this->_graphics_factory->FreeShader(vertex_shader);
	this->_graphics_factory->FreeShader(fragment_shader);
	this->_cube.SetShaderProgram(program);
}

void TestScene::BuildMesh()
{
	Cube::CreateMesh(this->_graphics_factory);
}

void TestScene::CreateKeyboardBindings()
{
	this->_keyboard.Add(KeyBinding(KeyCode::W, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(this->_camera.GetForward() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::S, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(-this->_camera.GetForward() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::D, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(this->_camera.GetRight() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::A, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(-this->_camera.GetRight() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Space, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(this->_camera.GetUp() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::LeftControl, KeyBindingState::Held, [&] { this->_camera.TranslatePosition(-this->_camera.GetUp() * 20.0f * (float)this->GetDeltaTime()); }));

	this->_keyboard.Add(KeyBinding(KeyCode::Left, KeyBindingState::Held, [&] { this->_camera.TranslateRotation(Vector3F(0.0f, -60.0f * this->GetDeltaTime(), 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Right, KeyBindingState::Held, [&] { this->_camera.TranslateRotation(Vector3F(0.0f, 60.0f * this->GetDeltaTime(), 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Up, KeyBindingState::Held, [&] { this->_camera.TranslateRotation(Vector3F(-60.0f * this->GetDeltaTime(), 0.0f, 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Down, KeyBindingState::Held, [&] { this->_camera.TranslateRotation(Vector3F(60.0f * this->GetDeltaTime(), 0.0f, 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Escape, KeyBindingState::Pressed, [&] { this->_app->Close(); }));
}

void TestScene::Load()
{
	this->BuildShaderProgram();
	this->BuildMesh();
	this->CreateKeyboardBindings();
	
	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, 5.0f));

	this->SceneBase::Load();
}

void TestScene::Update()
{
	this->SceneBase::Update();

	float rotation = (float)(60.0f * this->_delta_time);
	this->_cube.GetTransform()->RotateRelative(glm::vec3(rotation, rotation, rotation));
}

void TestScene::Render()
{
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_camera.SetAspectRatio((float)width / height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, width, height);

	// Render Scene
	Matrix4F mvp = this->_camera.GetProjectionMatrix() * this->_camera.GetViewMatrix() * this->_cube.GetTransform()->GetModelMatrix();
	this->_cube.Render(this->_renderer, [&](ShaderProgram*& shader_program)
	{
		shader_program->SetUniform("mvp", mvp);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void TestScene::Dispose()
{
	Cube::FreeMesh(this->_graphics_factory);
	this->_graphics_factory->FreeShaderProgram(this->_cube.GetShaderProgram());
}