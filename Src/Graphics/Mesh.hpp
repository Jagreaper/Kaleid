#pragma once

#include "stdafx.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "TextureBase.hpp"
#include <vector>
#include <functional>

API_BEGIN
namespace Kaleid::Graphics
{
	class Mesh
	{
	public:
		KALEID_GRAPHICS_API void MakeCurrent();
		void Render(const ShaderProgram* shader, const std::vector<TextureBase*>* textures, std::function<void()> arguments = NULL);
		const GLuint GetVertexArrayId() const;
		const IndexBuffer* GetIndexBuffer() const;
		const std::vector<VertexBuffer*>* GetVertexBuffers() const;
		bool HasIndexBuffer() const;
		bool HasVertexBuffers() const;
		const size_t GetBestVboLength() const;
#ifdef KALEID_GRAPHICS_DLL
		Mesh();
		Mesh(IndexBuffer* ibo, VertexBuffer* vbo);
		Mesh(IndexBuffer* ibo, std::vector<VertexBuffer*>* vbos);
		void Dispose();
	private:
		void BuildVertexArray();

		GLuint _vao_id;
		IndexBuffer* _ibo;
		std::vector<VertexBuffer*> _vbos;
		size_t _b_vbo_length;
#endif
	};
}
API_END