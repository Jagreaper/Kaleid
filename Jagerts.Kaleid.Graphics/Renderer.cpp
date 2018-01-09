#include "Renderer.hpp"
#include "TextureBase.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

using namespace Jagerts::Kaleid::Graphics;

#if DEBUG

void Renderer::ErrorCheck()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
}

#define _ERROR_CHECK this->ErrorCheck();
#else
#define _ERROR_CHECK
#endif

Renderer::Renderer(bool use_defaults)
{
	this->_use_defaults = use_defaults;
	this->_is_loaded = false;
}

void Renderer::Load()
{
	if (!this->_is_loaded)
	{
		if (this->_use_defaults)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
		}

		this->_is_loaded = true;
	}
	
	_ERROR_CHECK
}

bool Renderer::IsLoaded()
{
	return this->_is_loaded;
}

void Renderer::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_ERROR_CHECK
}

void Renderer::SetViewport(float x, float y, float width, float height)
{
	glViewport((int)x, (int)y, (int)width, (int)height);
	_ERROR_CHECK
}

void Renderer::SetWireframeMode(bool enabled)
{
	if (enabled)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::BindTexture(TextureBase* tex, int level)
{
	if (tex != NULL)
	{
		glActiveTexture(GL_TEXTURE0 + level);
		glBindTexture(tex->_type_info, tex->_id);
	}
}

void Renderer::BindTextures(std::vector<TextureBase*>& textures)
{
	if (textures.size() > 0)
	{
		for (unsigned int index = 0; index < textures.size(); index++)
			this->BindTexture(textures[index], index);
	}

	_ERROR_CHECK
}

void Renderer::BindTextures(std::vector<TextureBase*>* textures)
{
	if (textures != NULL && textures->size() > 0)
	{
		for (unsigned int index = 0; index < textures->size(); index++)
			this->BindTexture(textures->at(index), index);
	}

	_ERROR_CHECK
}

#define _RENDER_MESH \
if (mesh->HasIndexBuffer()) \
{ \
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndexBuffer()->_id); \
	glDrawElements(mesh->_primitive_type, (GLsizei)mesh->GetIndexBuffer()->GetLength(), mesh->GetIndexBuffer()->_type_info, NULL); \
} \
else \
	glDrawArrays(mesh->_primitive_type, 0, (GLsizei)mesh->_b_vbo_length); \
_ERROR_CHECK \

#define _USE_MESH \
glBindVertexArray(mesh->_vao_id); \
glUseProgram(shader_program->_id); \

#define _CHECK_MESH_FIELDS \
if (shader_program == NULL || !mesh->HasVertexBuffers()) \
	throw std::runtime_error("Missing fields to render mesh"); \

#define _TEXTURE_MESH \
_CHECK_MESH_FIELDS \
\
this->BindTextures(textures); \
_USE_MESH \
if (arguments != NULL) \
	arguments(shader_program); \
_RENDER_MESH \

#define _TEXTURE_MESH_METHOD(PTR) \
void Renderer::RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>PTR textures, std::function<void(ShaderProgram*&)> arguments) \
{ \
	_TEXTURE_MESH \
} \

_TEXTURE_MESH_METHOD(&)
_TEXTURE_MESH_METHOD(*)

#undef _TEXTURE_MESH_METHOD
#undef _TEXTURE_MESH

void Renderer::RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, Material* material, std::function<void(ShaderProgram*&, Material*)> arguments)
{
	_CHECK_MESH_FIELDS
	
	_USE_MESH
	if (arguments != NULL)
		arguments(shader_program, material);
	_RENDER_MESH
}

#undef _CHECK_MESH_FIELDS
#undef _USE_MESH
#undef _RENDER_MESH
#undef _ERROR_CHECK