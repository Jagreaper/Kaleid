#include "stdafx.hpp"
#include "RootScene.hpp"
#include "MtlMaterialDecoder.hpp"
#include "ObjModelDecoder.hpp"
#include "TextureDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "App.hpp"
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
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
	layout(location = 1) in vec3 np;
	layout(location = 2) in vec2 tc;

	out vec2 texel;

	uniform mat4 mvp;

	void main()
	{
		texel = tc;
		texel.y = texel.y;
		gl_Position = mvp * vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	const char* fragment_source = R"(
	#version 410
	
	in vec2 texel;
	
	out vec4 frag_colour;

	uniform mat4 mvp;
	uniform vec3 ka;
	uniform sampler2D ka_tex;

	void main()
	{
		frag_colour = texture2D(ka_tex, texel) * vec4(ka.x, ka.y, ka.z, 1.0);
	}

	)";

	Shader* vertex_shader = this->_graphics_factory->CreateShader(&vertex_source, ShaderType::Vertex);
	Shader* fragment_shader = this->_graphics_factory->CreateShader(&fragment_source, ShaderType::Fragment);

	this->_program = this->_graphics_factory->CreateShaderProgram();
	this->_program->Attach(vertex_shader);
	this->_program->Attach(fragment_shader);
	this->_program->Link();
	this->_program->Dettach(vertex_shader);
	this->_program->Dettach(fragment_shader);

	this->_graphics_factory->FreeShader(vertex_shader);
	this->_graphics_factory->FreeShader(fragment_shader);
}

void RootScene::BuildMesh()
{
	ModelDecoderParams obj_params;
	obj_params.GraphicsFactory = this->_graphics_factory;
	obj_params.ModelDecoderParamsArg = ModelDecoderParamsArg::Center;

	Texture* texture = this->_graphics_factory->CreateTexture();
	const char* tex_path = "Assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.tga";
	TexturePathDecoder tex_decoder;
	tex_decoder.TryDecode(tex_path, texture, NULL);

	std::vector<MaterialInfo> materials;
	const char* mtl_path = "Assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.mtl";
	MtlMaterialPathDecoder mtl_decoder;
	mtl_decoder.TryDecode(mtl_path, &materials, NULL);

	Model* model = Model::AllocateMemory();
	const char* obj_path = "Assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.obj";
	ObjModelPathDecoder obj_decoder;
	obj_params.Materials = &materials;
	obj_params.ModelDecoderParamsArg = ModelDecoderParamsArg::Center;
	obj_decoder.TryDecode(obj_path, model, obj_params);

	for (int index = 0; index < model->GetComponents()->size(); index++)
	{
		ModelComponent* component = model->GetComponents()->at(index);
		component->SetShaderProgram(this->_program);
		component->GetMaterial().AmbientTexture = component->GetMaterialInfo().AmbientTexture.length() > 0 ? (TextureBase*)texture : NULL;
	}

	this->_actor.AddModel("USA_PowerPlant_Base", model);

	this->_actor.GetTransform()->SetRelativePosition(Vector3F(30.0f, 0.0f, 0.0f));
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

void RootScene::Load()
{
	this->BuildShaderProgram();
	this->BuildMesh();
	this->CreateKeyboardBindings();

	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, 5.0f));
	this->_camera.SetFarZ(2000.0f);

	this->SceneBase::Load();
}

void RootScene::Update()
{
	this->SceneBase::Update();
}

void RootScene::Render()
{
	// Setup Scene
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_camera.SetAspectRatio((float)width / height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, width, height);

	Matrix4F mvp = (&this->_camera)->GetProjectionMatrix() * (&this->_camera)->GetViewMatrix() * this->_actor.GetTransform()->GetModelMatrix();
	Renderer* renderer = this->_renderer;

	this->_actor.Render(this->_renderer, [&] (ShaderProgram*& shader_program, Material* material)
	{
		if (material->AmbientTexture != NULL)
			renderer->BindTexture(material->AmbientTexture);

		shader_program->SetUniform("mvp", mvp);
		shader_program->SetUniform("ka", material->AmbientColor);
		shader_program->SetUniform("ka_tex", 0);
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