#include "RootScene.hpp"
#include "Jagerts.Kaleid.IO/MtlMaterialDecoder.hpp"
#include "Jagerts.Kaleid.IO/ObjModelDecoder.hpp"
#include "Jagerts.Kaleid.IO/TextureDecoder.hpp"
#include "Jagerts.Kaleid.Graphics/GraphicsFactory.hpp"
#include "Jagerts.Kaleid.Graphics/Shader.hpp"
#include "Jagerts.Kaleid.Graphics/ShaderProgram.hpp"
#include "Jagerts.Kaleid.Game/App.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"
#include "Jagerts.Kaleid.Graphics/Mesh.hpp"
#include "Jagerts.Kaleid.Game/Model.hpp"
#include "Jagerts.Kaleid.Graphics/Window.hpp"
#include "Jagerts.Kaleid.Math/Matrix.hpp"
#include "Jagerts.Kaleid.Input/Keyboard.hpp"
#include "Jagerts.Kaleid.Input/KeyBinding.hpp"
#include "Jagerts.Kaleid.Input/MouseMoveBinding.hpp"
#include "Jagerts.Felcp.Helpers/VectorHelper.hpp"
#include "Jagerts.Felcp.Imaging/Image.hpp"
#include "Jagerts.Felcp.Xml/XmlFile.hpp"
#include "Jagerts.Felcp.IO.Xml/XmlDecoder.hpp"
#include <iostream>
#include <fstream>

using namespace Jagerts::Kaleid::Math;
using namespace Jagerts::Kaleid::Game;
using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Kaleid::IO;
using namespace Jagerts::Kaleid::Input;
using namespace Jagerts::Felcp::Helpers;
using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO::Xml;
using namespace Jagerts::Felcp::Imaging;
using namespace Jagerts::Bezel;

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

	uniform bool has_ka_tex;

	void main()
	{
		if (has_ka_tex == true)
			frag_colour = texture2D(ka_tex, texel) * vec4(ka.x, ka.y, ka.z, 1.0);
		else
			frag_colour = vec4(ka.x, ka.y, ka.z, 1.0);
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
	const char* tex_path = "assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.tga";
	TextureDecoder tex_decoder;
	tex_decoder.TryDecode(tex_path, texture, NULL);

	std::vector<MaterialInfo> materials;
	const char* mtl_path = "assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.mtl";
	MtlMaterialDecoder mtl_decoder;
	mtl_decoder.TryDecode(mtl_path, &materials, NULL);

	Model* model = Model::AllocateMemory();
	const char* obj_path = "assets\\Models\\USA Power Plant\\USA_PowerPlant_Base.obj";
	ObjModelDecoder obj_decoder;
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

void RootScene::CameraMouseMovement(const double& x_delta, const double& y_delta)
{
	if (x_delta != 0 || y_delta != 0)
	{
		Vector3F vec(y_delta * 120.0 * this->GetDeltaTime(), x_delta * 120.0 * this->GetDeltaTime(), 0.0f);
		this->_camera.GetTransform()->RotateRelative(vec);
	}
}

void RootScene::CreateKeyboardBindings()
{
	this->_keyboard.Add(KeyBinding(KeyCode::W, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(this->_camera.GetTransform()->GetRelativeForward() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::S, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(-this->_camera.GetTransform()->GetRelativeForward() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::D, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(this->_camera.GetTransform()->GetRelativeRight() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::A, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(-this->_camera.GetTransform()->GetRelativeRight() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Space, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(this->_camera.GetTransform()->GetRelativeUp() * 20.0f * (float)this->GetDeltaTime()); }));
	this->_keyboard.Add(KeyBinding(KeyCode::LeftControl, KeyBindingState::Held, [&] { this->_camera.GetTransform()->TranslateRelative(-this->_camera.GetTransform()->GetRelativeUp() * 20.0f * (float)this->GetDeltaTime()); }));

	this->_mouse.Add(MouseMoveBinding(MouseMoveType::CenteredDelta, std::bind(&RootScene::CameraMouseMovement, this, std::placeholders::_1, std::placeholders::_2)));
	this->_keyboard.Add(KeyBinding(KeyCode::Left, KeyBindingState::Held, [&] { this->_camera.GetTransform()->RotateRelative(Vector3F(0.0f, -60.0f * this->GetDeltaTime(), 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Right, KeyBindingState::Held, [&] { this->_camera.GetTransform()->RotateRelative(Vector3F(0.0f, 60.0f * this->GetDeltaTime(), 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Up, KeyBindingState::Held, [&] { this->_camera.GetTransform()->RotateRelative(Vector3F(-60.0f * this->GetDeltaTime(), 0.0f, 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Down, KeyBindingState::Held, [&] { this->_camera.GetTransform()->RotateRelative(Vector3F(60.0f * this->GetDeltaTime(), 0.0f, 0.0f)); }));
	this->_keyboard.Add(KeyBinding(KeyCode::Escape, KeyBindingState::Pressed, [&] { this->_app->Close(); }));
}


void DecodeXml(XmlFile* xml)
{
	const char* xml_path = "D:\\Users\\James\\Desktop\\Xml Test.xml";
	XmlDecoder xml_decoder;
	xml_decoder.TryDecode(xml_path, xml);
}


void RootScene::Load()
{
	XmlFile xml;
	DecodeXml(&xml);
	this->BuildShaderProgram();
	this->BuildMesh();
	this->CreateKeyboardBindings();

	this->_camera.GetTransform()->SetRelativePosition(Vector3F(0.0f, 0.0f, 5.0f));
	this->_camera.SetFarZ(2000.0f);

	this->SceneBase::Load();
	this->_app->GetWindow(0)->SetCursorMode(CursorMode::Hidden);

	this->font = new Font("C:\\Windows\\Fonts\\Arial.ttf");
}

void RootScene::Update()
{
	this->_app->GetWindow(0)->CenterCursor();
	this->SceneBase::Update();
}

void RootScene::Render()
{
	// Setup Scene
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_camera.SetAspectRatio((float)width / height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, (float)width, (float)height);

	Matrix4F mvp = (&this->_camera)->GetProjectionMatrix() * (&this->_camera)->GetViewMatrix() * this->_actor.GetTransform()->GetModelMatrix();
	Renderer* renderer = this->_renderer;

	this->_actor.Render(this->_renderer, [&] (ShaderProgram*& shader_program, Material* material)
	{
		if (material->AmbientTexture != NULL)
		{
			renderer->BindTexture(material->AmbientTexture);
			shader_program->SetUniform("ka_tex", 0);
			shader_program->SetUniform("has_ka_tex", true);
		}
		else
			shader_program->SetUniform("has_ka_tex", false);


		shader_program->SetUniform("mvp", mvp);
		shader_program->SetUniform("ka", material->AmbientColor);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();

	renderer->RenderText(this->font, "Hello World!", 48, Vector3F(1.0f, 0.0f, 0.0f), Vector2F(0.0f, 0.0f), Vector2F(0.5f, 0.5f));
}

void RootScene::Dispose()
{
	delete this->font;
	//this->_graphics_factory->FreeShaderProgram(this->_model.GetShaderProgram());
	//this->_graphics_factory->FreeIndexBuffer(this->_model.GetMesh()->GetIndexBuffer());
	//this->_graphics_factory->FreeVertexBuffers(this->_model.GetMesh()->GetVertexBuffers());
	//this->_graphics_factory->FreeMesh(this->_model.GetMesh());
}