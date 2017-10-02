#include "stdafx.hpp"
#include "RootScene.hpp"
#include "ObjStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Window.hpp"
#include "Matrix.hpp"
#include "Keyboard.hpp"
#include "KeyBinding.hpp"
#include "Image.hpp"
#include "PngStreamDecoder.hpp"
#include <iostream>
#include <fstream>

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::IO;
using namespace Kaleid::Input;
using namespace Kaleid::Imaging;

RootScene::RootScene(App* app)
	: SceneBase(app)
{
	// Skip
}


void RootScene::BuildShaderProgram()
{
	const char* vertex_source = R"(
	#version 410

	layout(location = 0) in vec3 vp;

	uniform mat4 mvp;

	void main()
	{
		gl_Position = mvp * vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	const char* fragment_source = R"(
	#version 410

	out vec4 frag_colour;

	uniform mat4 mvp;

	void main()
	{
		frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
	}

	)";

	Shader* vertex_shader = this->_graphics_factory->CreateShader(&vertex_source, ShaderType::Vertex);
	Shader* fragment_shader = this->_graphics_factory->CreateShader(&fragment_source, ShaderType::Fragment);

	ShaderProgram* program = this->_graphics_factory->CreateShaderProgram();
	program->Attach(vertex_shader);
	program->Attach(fragment_shader);
	program->Link();
	program->Dettach(vertex_shader);
	program->Dettach(fragment_shader);

	this->_graphics_factory->FreeShader(vertex_shader);
	this->_graphics_factory->FreeShader(fragment_shader);
	this->_model.SetShaderProgram(program);
}

void RootScene::BuildMesh()
{
	const char* path = "Models\\Stormtrooper\\Stormtrooper.obj";
	std::ifstream obj_stream;
	obj_stream.open(path);
	ObjStreamDecoder decoder;
	decoder.TryDecode(obj_stream, &this->_model, this->_graphics_factory);
	obj_stream.close();
}

void RootScene::CreateKeyboardBindings()
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
}

double RootScene::GetDeltaTime()
{
	return this->_delta_time;
}

void RootScene::Load()
{
	this->BuildMesh();
	this->BuildShaderProgram();
	this->CreateKeyboardBindings();

	Image image;

	const char* path = "D:\\Users\\James\\Pictures\\Misc\\Fate zero Saber by tidusafx on DeviantArt.png";
	std::ifstream obj_stream(path, std::ios_base::in | std::ios_base::binary);
	PngStreamDecoder decoder;
	decoder.TryDecode(obj_stream, &image);
	obj_stream.close();

	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, 5.0f));

	this->_o_time = clock();
}

void RootScene::Update()
{
	this->_n_time = clock();
	this->_delta_time = (double)(this->_n_time - this->_o_time) / CLOCKS_PER_SEC;
	this->_o_time = this->_n_time;
}

void RootScene::Render()
{
	// Setup Scene
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, width, height);

	this->_renderer->SetWireframeMode(true);
	// Render Scene
	ShaderProgram* shader_program = this->_model.GetShaderProgram();
	Matrix4F mvp = (&this->_camera)->GetProjectionMatrix() * (&this->_camera)->GetViewMatrix() * this->_model.GetTransform()->GetModelMatrix();

	this->_model.Render(this->_renderer, [&]
	{
		shader_program->SetUniform("mvp", mvp);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void RootScene::Dispose()
{
	this->_graphics_factory->FreeShaderProgram(this->_model.GetShaderProgram());
	this->_graphics_factory->FreeIndexBuffer(this->_model.GetMesh()->GetIndexBuffer());
	this->_graphics_factory->FreeVertexBuffers(this->_model.GetMesh()->GetVertexBuffers());
	this->_graphics_factory->FreeMesh(this->_model.GetMesh());
}