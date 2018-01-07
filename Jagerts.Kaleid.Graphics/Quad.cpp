#include "Quad.hpp"

#include "Jagerts.Kaleid.Graphics\Renderer.hpp"
#include "Jagerts.Kaleid.Graphics\Mesh.hpp"
#include "Jagerts.Kaleid.Graphics\GraphicsFactory.hpp"
#include "Jagerts.Felcp.Helpers\VectorHelper.hpp"

#define _QuadShapeMeshData \
const float verticies[] = \
{ \
	-1.0f, -1.0f,  0.0f, \
	 1.0f, -1.0f,  0.0f, \
	 1.0f,  1.0f,  0.0f, \
	-1.0f,  1.0f,  0.0f, \
}; \
\
const unsigned int indicies[] = \
{ \
	0, 1, 2, \
	2, 3, 0, \
}; \
\
VertexBuffer* vertex_buffer = graphics_factory->CreateVertexBuffer(verticies, 12, 3); \
IndexBuffer* index_buffer = graphics_factory->CreateIndexBuffer(indicies, 6); \
Mesh* mesh = graphics_factory->CreateMesh(index_buffer, vertex_buffer) \

jkgRenderableShapeStaticSource(Quad, _QuadShapeMeshData)

#undef _QuadShapeMeshData