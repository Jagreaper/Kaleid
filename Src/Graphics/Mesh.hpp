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
		void Compose();
		void SetIndexBuffer(IndexBuffer* buffer);
		void SetVertexBuffers(std::vector<VertexBuffer*>* buffers);
		const IndexBuffer* GetIndexBuffer() const;
		const std::vector<VertexBuffer*>* GetVertexBuffers() const;
		const size_t GetBestVboLength() const;
		bool HasIndexBuffer() const;
		bool HasVertexBuffers() const;
		void Render(const ShaderProgram* shader, const std::vector<TextureBase*>* textures, std::function<void()> arguments);
#ifdef KALEID_GRAPHICS_DLL
		Mesh();
		void Dispose();
		const unsigned int GetVertexArrayId() const;
	private:
		unsigned int _vao_id;
		IndexBuffer* _ibo;
		std::vector<VertexBuffer*>* _vbos;
		size_t _b_vbo_length;
#endif
	};
}
API_END