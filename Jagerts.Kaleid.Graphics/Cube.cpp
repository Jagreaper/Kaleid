#include "Cube.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"
#include "Jagerts.Kaleid.Graphics/Mesh.hpp"
#include "Jagerts.Kaleid.Graphics/GraphicsFactory.hpp"
#include "Jagerts.Felcp.Helpers/VectorHelper.hpp"

#define _CubeShapeMeshData \
const float verticies[] = \
{ \
	-1.0f, -1.0f,  1.0f, \
	 1.0f, -1.0f,  1.0f, \
	 1.0f,  1.0f,  1.0f, \
	-1.0f,  1.0f,  1.0f, \
\
	-1.0f, -1.0f, -1.0f, \
	 1.0f, -1.0f, -1.0f, \
	 1.0f,  1.0f, -1.0f, \
	-1.0f,  1.0f, -1.0f, \
}; \
\
const unsigned int indicies[] = \
{ \
	0, 1, 2, \
	2, 3, 0, \
\
	1, 5, 6, \
	6, 2, 1, \
\
	7, 6, 5, \
	5, 4, 7, \
\
	4, 0, 3, \
	3, 7, 4, \
\
	4, 5, 1, \
	1, 0, 4, \
\
	3, 2, 6, \
	6, 7, 3, \
}; \
\
VertexBuffer* vertex_buffer = graphics_factory->CreateVertexBuffer(verticies, 24, 3); \
IndexBuffer* index_buffer = graphics_factory->CreateIndexBuffer(indicies, 36); \
Mesh* mesh = graphics_factory->CreateMesh(index_buffer, vertex_buffer) \

jkgRenderableShapeStaticSource(Cube, _CubeShapeMeshData)

#undef _CubeShapeMeshData