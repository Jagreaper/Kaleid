#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"
#include <functional>

namespace Jagerts::Kaleid::Graphics
{
	class Mesh;
	class ShaderProgram;
	class Renderer;
	class GraphicsFactory;

	class JAGERTS_KALEID_GRAPHICS_API RenderableShape : public Jagerts::Kaleid::Math::TransformableObject
	{
	public:
		void Render(Jagerts::Kaleid::Graphics::Renderer*& renderer, std::function<void(Jagerts::Kaleid::Graphics::ShaderProgram*&)> arguments);
		void SetShaderProgram(Jagerts::Kaleid::Graphics::ShaderProgram*& shader_program);
		Jagerts::Kaleid::Graphics::ShaderProgram* GetShaderProgram();
		jkmUsingTransformableObject;
	protected:
		Jagerts::Kaleid::Graphics::Mesh* _mesh;
		Jagerts::Kaleid::Graphics::ShaderProgram* _shader_program;

		friend class Quad;
		friend class Cube;
		friend class Point;
	};
}

#define jkgUsingRenderableShape \
using Jagerts::Kaleid::Graphics::RenderableShape::Render; \
using Jagerts::Kaleid::Graphics::RenderableShape::SetShaderProgram; \
using Jagerts::Kaleid::Graphics::RenderableShape::GetShaderProgram \

#define jkgRenderableShapeStaticHeader \
public: \
	static bool MeshExists(); \
	static Jagerts::Kaleid::Graphics::Mesh* CreateMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory); \
	static Jagerts::Kaleid::Graphics::Mesh* GetMesh(); \
	static void FreeMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory); \
protected: \
	static Jagerts::Kaleid::Graphics::Mesh* _s_mesh; \
	static std::vector<RenderableShape*> _shapes \

#ifdef JAGERTS_KALEID_GRAPHICS_DLL
#define jkgRenderableShapeStaticSource(_CLASS, _DATA) \
\
using namespace Jagerts::Kaleid::Math; \
using namespace Jagerts::Kaleid::Graphics; \
using namespace Jagerts::Felcp::Helpers; \
\
Mesh* _CLASS::_s_mesh = NULL; \
std::vector<RenderableShape*> _CLASS::_shapes = std::vector<RenderableShape*>(); \
\
_CLASS::_CLASS() \
{ \
	this->_mesh = _CLASS::_s_mesh; \
	this->_shader_program = NULL; \
	this->_shapes.push_back(this); \
} \
\
_CLASS::~_CLASS() \
{ \
	VectorHelper::RemoveItem(_CLASS::_shapes, (RenderableShape*)this); \
} \
 \
bool _CLASS::MeshExists() \
{ \
	return _CLASS::_s_mesh != NULL; \
} \
 \
Mesh* _CLASS::CreateMesh(GraphicsFactory*& graphics_factory) \
{ \
	if (_CLASS::_s_mesh == NULL) \
	{ \
		_DATA; \
		_CLASS::_s_mesh = mesh; \
		_CLASS::_s_mesh->Compose(); \
		 \
		for (RenderableShape*& shape : _CLASS::_shapes) \
			shape->_mesh = _CLASS::_s_mesh; \
	} \
 \
	return _CLASS::GetMesh(); \
} \
\
Mesh* _CLASS::GetMesh() \
{ \
	return _CLASS::_s_mesh; \
} \
\
void _CLASS::FreeMesh(GraphicsFactory*& graphics_factory) \
{ \
	graphics_factory->FreeIndexBuffer(_CLASS::_s_mesh->GetIndexBuffer()); \
	graphics_factory->FreeVertexBuffers(_CLASS::_s_mesh->GetVertexBuffers()); \
	graphics_factory->FreeMesh(_CLASS::_s_mesh); \
 \
	for (RenderableShape*& shape : _CLASS::_shapes) \
		shape->_mesh = NULL; \
} \

#endif