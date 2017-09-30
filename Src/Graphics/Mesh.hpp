#pragma once

#include "stdafx.hpp"
#include <vector>
#include <functional>

API_BEGIN
namespace Kaleid::Graphics
{
	enum PrimitiveType
	{
		Points = 0x0000,
		Lines = 0x0001,
		LineLoop = 0x0002,
		LineStrip = 0x0003,
		LinesAdjacency = 0x000A,
		LinesStripAdjacency = 0x000B,
		Triangles = 0x0004,
		TriangleStrip = 0x0005,
		TriangleAdjacency = 0x000C,
		TriangleStripAdjacency = 0x000D,
		Patches = 0xE,
	};

	class GraphicsFactory;
	class Renderer;
	class IndexBuffer;
	class VertexBuffer;
	class ShaderProgram;
	class TextureBase;

	class KALEID_GRAPHICS_API Mesh sealed
	{
	public:
		void Compose();
		void SetIndexBuffer(IndexBuffer* buffer);
		void SetVertexBuffers(std::vector<VertexBuffer*>* buffers);
		void SetPrimitiveType(const PrimitiveType type);
		IndexBuffer* GetIndexBuffer() const;
		std::vector<VertexBuffer*>* GetVertexBuffers();
		PrimitiveType GetPrimitiveType();
		bool HasIndexBuffer() const;
		bool HasVertexBuffers() const;
	private:
		Mesh();
		void Dispose();

		unsigned int _vao_id;
		IndexBuffer* _ibo;
		std::vector<VertexBuffer*> _vbos;
		size_t _b_vbo_length;
		PrimitiveType _primitive_type;

		friend class GraphicsFactory;
		friend class Renderer;
	};
}
API_END