#include "Point.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"
#include "Jagerts.Kaleid.Graphics/Mesh.hpp"
#include "Jagerts.Kaleid.Graphics/GraphicsFactory.hpp"
#include "Jagerts.Felcp.Helpers/VectorHelper.hpp"

#define _PointShapeMeshData \
const float verticies[] = \
{ \
	-0.0f, -0.0f,  0.0f, \
}; \
\
const unsigned int indicies[] = \
{ \
	0, \
}; \
\
VertexBuffer* vertex_buffer = graphics_factory->CreateVertexBuffer(verticies, 3, 3); \
IndexBuffer* index_buffer = graphics_factory->CreateIndexBuffer(indicies, 1); \
Mesh* mesh = graphics_factory->CreateMesh(index_buffer, vertex_buffer); \
mesh->SetPrimitiveType(PrimitiveType::Points) \

jkgRenderableShapeStaticSource(Point, _PointShapeMeshData)

#undef _PointShapeMeshData