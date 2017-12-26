#include "stdafx.hpp"
#include "RootScene.hpp"
#include "MtlMaterialStreamDecoder.hpp"
#include "ObjModelStreamDecoder.hpp"
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
#include "VectorHelper.hpp"
#include "Image.hpp"
#include <iostream>
#include <fstream>

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::IO;
using namespace Kaleid::Input;
using namespace Kaleid::Imaging;
using namespace Kaleid::Application;
using namespace Kaleid::Helpers;

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
	uniform vec3 ka;

	void main()
	{
		frag_colour = vec4(ka.x, ka.y, ka.z, 1.0);
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
	for (int index = 0; index < this->_model.GetComponents()->size(); index++)
		(*(this->_model.GetComponents()))[index].SetShaderProgram(program);
}

void RootScene::BuildMesh()
{
	std::vector<MaterialInfo> materials;
	const char* mtl_path = "Assets\\Models\\USA Power Plant\\PowerPlant_Base_Normal.mtl";
	std::ifstream mtl_stream;
	mtl_stream.open(mtl_path);
	MtlMaterialStreamDecoder mtl_decoder;
	mtl_decoder.TryDecode(mtl_stream, &materials, NULL);
	mtl_stream.close();

	const char* obj_path = "Assets\\Models\\USA Power Plant\\PowerPlant_Base_Normal.obj";
	std::ifstream obj_stream;
	obj_stream.open(obj_path);
	ObjModelStreamDecoder obj_decoder;
	ModelDecoderParams obj_params;
	obj_params.GraphicsFactory = this->_graphics_factory;
	obj_params.Materials = &materials;
	obj_params.ModelDecoderParamsArg = ModelDecoderParamsArg::Center;
	obj_decoder.TryDecode(obj_stream, &this->_model, obj_params);
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
	this->_keyboard.Add(KeyBinding(KeyCode::Escape, KeyBindingState::Pressed, [&] { this->_app->Close(); }));
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
	Matrix4F mvp = (&this->_camera)->GetProjectionMatrix() * (&this->_camera)->GetViewMatrix() * this->_model.GetTransform()->GetModelMatrix();

	this->_model.Render(this->_renderer, [&] (ShaderProgram*& shader_program, Material* material)
	{
		shader_program->SetUniform("mvp", mvp);
		shader_program->SetUniform("ka", material->AmbientColor);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void RootScene::Dispose()
{
	//this->_graphics_factory->FreeShaderProgram(this->_model.GetShaderProgram());
	//this->_graphics_factory->FreeIndexBuffer(this->_model.GetMesh()->GetIndexBuffer());
	//this->_graphics_factory->FreeVertexBuffers(this->_model.GetMesh()->GetVertexBuffers());
	//this->_graphics_factory->FreeMesh(this->_model.GetMesh());
}