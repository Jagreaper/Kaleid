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

	void main()
	{
		gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	const char* fragment_source = R"(
	#version 410

	out vec4 frag_colour;

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
	this->_shader_program = program;
}

void TestScene::BuildMesh()
{
	float verticies[] =
	{
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	unsigned int indicies[] =
	{
		0, 1, 2,
	};

	VertexBuffer* vertex_buffer = this->_graphics_factory->CreateVertexBuffer(verticies, 9, 3);
	IndexBuffer* index_buffer = this->_graphics_factory->CreateIndexBuffer(indicies, 3);
	this->_mesh = this->_graphics_factory->CreateMesh(index_buffer, vertex_buffer);
	this->_mesh->Compose();
}

void TestScene::Load()
{
	//this->_app->GetWindow(0)->MakeCurrent();

	this->BuildShaderProgram();
	this->BuildMesh();
	

	this->_camera.SetPosition(Vector3F(0.0f, 0.0f, -5.0f));
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
	ShaderProgram* shader_program = this->_shader_program;

	this->_renderer->RenderMesh(this->_mesh, this->_shader_program, NULL, NULL);

	// Cleanup Scene
	this->_app->GetWindow(0)->SwapBuffers();
}

void TestScene::Dispose()
{
	this->_graphics_factory->FreeShaderProgram(this->_shader_program);
	this->_graphics_factory->FreeIndexBuffer(this->_mesh->GetIndexBuffer());
	this->_graphics_factory->FreeVertexBuffers(this->_mesh->GetVertexBuffers());
	this->_graphics_factory->FreeMesh(this->_mesh);
}