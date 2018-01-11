#include "Font.hpp"
#include "GraphicsFactory.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Quad.hpp"
#include <FT/ft2build.h>
#include FT_FREETYPE_H

using namespace Jagerts::Kaleid::Math;
using namespace Jagerts::Kaleid::Graphics;

Texture* Font::_texture = NULL;
ShaderProgram* Font::_shader_program = NULL;
Mesh* Font::_mesh = NULL;
Jagerts::Kaleid::Math::OrthographicCamera Font::_camera;
void* Font::_library = NULL;

#define _LIB_FT (FT_Library)_library

void CreateLibrary(void*& library)
{
	FT_Library ft_lib;
	if (!FT_Init_FreeType(&ft_lib))
		library = (void*)ft_lib;
	else
		throw new std::runtime_error("Could not init freetype library\n");
}

void CreateFace(void*& face, const char* font, void* library)
{
	FT_Face ft_face;
	if (!FT_New_Face((FT_Library)library, font, 0, &ft_face))
		face = (void*)ft_face;
	else
		throw new std::runtime_error("Could not open font\n");
}

void CreateShaderProgram(GraphicsFactory* factory, ShaderProgram*& shader_program)
{
	const char* vertex_source = R"(
	#version 410

	layout(location = 0) in vec3 vp;
	layout(location = 1) in vec2 tc;

	out vec2 texel;

	uniform mat4 mvp;

	void main()
	{
		texel = tc;
		gl_Position = mvp * vec4(vp.x, vp.y, vp.z, 1.0);
	}

	)";

	const char* fragment_source = R"(
	#version 410
	
	in vec2 texel;
	
	out vec4 frag_color;

	uniform vec3 color;
	uniform sampler2D character;

	void main()
	{
		frag_color = texture2D(character, texel) * vec4(color.x, color.y, color.z, 1.0);
	}

	)";

	Shader* vertex_shader = factory->CreateShader(&vertex_source, ShaderType::Vertex);
	Shader* fragment_shader = factory->CreateShader(&fragment_source, ShaderType::Fragment);

	shader_program = factory->CreateShaderProgram();
	shader_program->Attach(vertex_shader);
	shader_program->Attach(fragment_shader);
	shader_program->Link();
	shader_program->Dettach(vertex_shader);
	shader_program->Dettach(fragment_shader);

	factory->FreeShader(vertex_shader);
	factory->FreeShader(fragment_shader);
}

void CreateMesh(GraphicsFactory* factory, Mesh*& mesh)
{
	mesh = Quad::CreateMesh(factory);
}

void CreateTextureProgram(GraphicsFactory* factory, Texture*& texture)
{
	texture = factory->CreateTexture();
	texture->SetParameter(TextureParameter::WrapS, TextureWrap::ClampToEdge);
	texture->SetParameter(TextureParameter::WrapT, TextureWrap::ClampToEdge);
	texture->SetParameter(TextureParameter::MinFilter, TextureMinFilter::Linear);
	texture->SetParameter(TextureParameter::MagFilter, TextureMinFilter::Linear);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

Font::Font(const char* font)
{
	if (Font::_library == NULL)
	{
		CreateLibrary(Font::_library);

		GraphicsFactory factory;
		if (Font::_shader_program == NULL)
			CreateShaderProgram(&factory, Font::_shader_program);

		if (Font::_mesh == NULL)
			CreateMesh(&factory, Font::_mesh);

		if (Font::_texture == NULL)
			CreateTextureProgram(&factory, Font::_texture);
	}

	if (this->_face == NULL)
		CreateFace(this->_face, font, Font::_library);
}

#undef _LIB_FT