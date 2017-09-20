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
			// TODO: Defaults
		}

		this->_is_loaded = true;
	}
}

bool Renderer::IsLoaded()
{
	return this->_is_loaded;
}

void Renderer::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
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
}

void Renderer::RenderMesh(Mesh*& mesh, ShaderProgram*& shader, std::vector<TextureBase*>& textures, std::function<void()> arguments)
{
	if (shader == NULL || !mesh->HasVertexBuffers())
		throw std::runtime_error("Missing fields to render mesh");

	this->BindTextures(textures);

	glBindVertexArray(mesh->_vao_id);
	glUseProgram(shader->_id);

	if (arguments != NULL)
		arguments();

	if (mesh->HasIndexBuffer())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIndexBuffer()->_id);
		glDrawElements(mesh->_primitive_type, (GLsizei)mesh->GetIndexBuffer()->GetLength(), mesh->GetIndexBuffer()->_type_info, NULL);
	}
	else
		glDrawArrays(mesh->_primitive_type, 0, (GLsizei)mesh->_b_vbo_length);
}