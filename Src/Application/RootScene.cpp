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
#include <iostream>
#include <fstream>

using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::IO;

RootScene::RootScene(App* app)
	: SceneBase(app)
{
	// Skip
}

void RootScene::Load()
{
	this->_app->GetWindow(0)->MakeCurrent();

	Cube::Load(this->_graphics_factory);

	// Read in parking lot model
	const char* path = "Models\\Parking Lot\\parking lot.obj";
	std::ifstream obj_stream;
	obj_stream.open(path);
	ObjStreamDecoder decoder;
	decoder.TryDecode(obj_stream, &this->_model, this->_graphics_factory);
	obj_stream.close();

	// Create Vertex Shader

	const char* vertex_source = R"(
	#version 410

	layout(location = 0) in vec3 vp;

	uniform mat4 mvp;

	void main()
	{
		gl_Position = mvp * vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	Shader* vertex_shader = this->_graphics_factory->CreateShader(ShaderType::Vertex);
	vertex_shader->SetSource(&vertex_source);
	vertex_shader->Compile();

	// Create Fragment Shader

	const char* fragment_source = R"(
	#version 410

	out vec4 frag_colour;

	uniform mat4 mvp;

	void main()
	{
		frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
	}

	)";

	Shader* fragment_shader = this->_graphics_factory->CreateShader(ShaderType::Fragment);
	fragment_shader->SetSource(&fragment_source);
	fragment_shader->Compile();

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
	this->_shader_program = program;
	this->_model.SetShaderProgram(program);
	this->_cube.SetShaderProgram(program);

	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, -5.0f));
}

void RootScene::Update()
{
	// Skip
}

void RootScene::Render()
{
	// Setup Scene
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, width, height);

	// Render Scene
	ShaderProgram* shader_program = this->_shader_program;
	Matrix4F mvp = this->_camera.GetProjectionMatrix() * this->_camera.GetViewMatrix() * this->_cube.GetTransform()->GetModelMatrix();

	this->_cube.Render(this->_renderer, [&, shader_program, mvp]
	{
		shader_program->SetUniform("mvp", mvp);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void RootScene::Dispose()
{
	Cube::Dispose(this->_graphics_factory);
	this->_graphics_factory->FreeShaderProgram(this->_model.GetShaderProgram());
	this->_graphics_factory->FreeIndexBuffer(this->_model.GetMesh()->GetIndexBuffer());
	this->_graphics_factory->FreeVertexBuffers(this->_model.GetMesh()->GetVertexBuffers());
	this->_graphics_factory->FreeMesh(this->_model.GetMesh());
}