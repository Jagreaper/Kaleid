#include "stdafx.hpp"
#include "Renderer.hpp"
#include "TextureBase.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

using namespace Kaleid::Graphics;

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

#if DEBUG
	this->ErrorCheck();
#endif
}

bool Renderer::IsLoaded()
{
	return this->_is_loaded;
}

void Renderer::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

#if DEBUG
	this->ErrorCheck();
#endif
}

void Renderer::SetViewport(float x, float y, float width, float height)
{
	glViewport(x, y, width, height);

#if DEBUG
	this->ErrorCheck();
#endif
}

void Renderer::BindTextures(std::vector<TextureBase*>& textures)
{
	if (textures.size() > 0)
	{
		for (unsigned int index = 0; index < textures.size(); index++)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(textures[index]->_type_info, textures[index]->_id);
		}
	}

#if DEBUG
	this->ErrorCheck();
#endif
}

void Renderer::BindTextures(std::vector<TextureBase*>* textures)
{
	if (textures != NULL && textures->size() > 0)
	{
		for (unsigned int index = 0; index < textures->size(); index++)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(textures->at(index)->_type_info, textures->at(index)->_id);
		}
	}

#if DEBUG
	this->ErrorCheck();
#endif
}

void Renderer::RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>& textures, std::function<void()> arguments)
{
	if (shader_program == NULL || !mesh->HasVertexBuffers())
		throw std::runtime_error("Missing fields to render mesh");

	this->BindTextures(textures);

	glBindVertexArray(mesh->_vao_id);
	glUseProgram(shader_program->_id);

	if (arguments != NULL)
		arguments();

	if (mesh->HasIndexBuffer())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndexBuffer()->_id);
		glDrawElements(mesh->_primitive_type, (GLsizei)mesh->GetIndexBuffer()->GetLength(), mesh->GetIndexBuffer()->_type_info, NULL);
	}
	else
		glDrawArrays(mesh->_primitive_type, 0, (GLsizei)mesh->_b_vbo_length);

#if DEBUG
	this->ErrorCheck();
#endif
}

void Renderer::RenderMesh(Mesh*& mesh, ShaderProgram*& shader_program, std::vector<TextureBase*>* textures, std::function<void()> arguments)
{
	if (shader_program == NULL || !mesh->HasVertexBuffers())
		throw std::runtime_error("Missing fields to render mesh");

	this->BindTextures(textures);

	glBindVertexArray(mesh->_vao_id);
	glUseProgram(shader_program->_id);

	if (arguments != NULL)
		arguments();

	if (mesh->HasIndexBuffer())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndexBuffer()->_id);
		glDrawElements(mesh->_primitive_type, (GLsizei)mesh->GetIndexBuffer()->GetLength(), mesh->GetIndexBuffer()->_type_info, NULL);
	}
	else
		glDrawArrays(mesh->_primitive_type, 0, (GLsizei)mesh->_b_vbo_length);

#if DEBUG
	this->ErrorCheck();
#endif
}


#if DEBUG

void Renderer::ErrorCheck()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		throw std::runtime_error("OpenGL Runtime Error");
}

#endif