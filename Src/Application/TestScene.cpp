#include "stdafx.hpp"
#include "TestScene.hpp"
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
	Cube::Load(this->_graphics_factory);
}

void TestScene::Load()
{
	//this->_app->GetWindow(0)->MakeCurrent();

	this->BuildShaderProgram();
	this->BuildMesh();
	
	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, 5.0f));
}

void TestScene::Update()
{
	// Skip
}

void TestScene::Render()
{
	this->_app->GetWindow(0)->MakeCurrent();
	// Setup Scene
	unsigned int width, height;
	this->_app->GetWindow(0)->GetSize(&width, &height);
	this->_renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	this->_renderer->SetViewport(0.0f, 0.0f, width, height);

	// Render Scene
	ShaderProgram* shader_program = this->_cube.GetShaderProgram();

	Matrix4F mvp = this->_camera.GetProjectionMatrix() * this->_camera.GetViewMatrix() * this->_cube.GetTransform()->GetModelMatrix();
	this->_cube.Render(this->_renderer, [&]
	{
		shader_program->SetUniform("mvp", mvp);
	});

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void TestScene::Dispose()
{
	Cube::Dispose(this->_graphics_factory);
	this->_graphics_factory->FreeShaderProgram(this->_cube.GetShaderProgram());
}