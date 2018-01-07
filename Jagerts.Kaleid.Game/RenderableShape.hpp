#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Math\Transform.hpp"
#include <functional>
#include "Model.hpp"

namespace Jagerts::Kaleid::Game
{
	class JAGERTS_KALEID_GAME_API RenderableShape : public Jagerts::Kaleid::Math::TransformableObject
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
using Jagerts::Kaleid::Game::RenderableShape::Render; \
using Jagerts::Kaleid::Game::RenderableShape::SetShaderProgram; \
using Jagerts::Kaleid::Game::RenderableShape::GetShaderProgram \

#define jkgRenderableShapeStaticHeader \
public: \
	static bool MeshExists(); \
	static Jagerts::Kaleid::Graphics::Mesh* CreateMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory); \
	static Jagerts::Kaleid::Graphics::Mesh* GetMesh(); \
	static void FreeMesh(Jagerts::Kaleid::Graphics::GraphicsFactory*& graphics_factory); \
protected: \
	static Jagerts::Kaleid::Graphics::Mesh* _s_mesh; \
	static std::vector<RenderableShape*> _shapes \

#ifdef JAGERTS_KALEID_GAME_DLL
#define jkgRenderableShapeStaticSource(CLASS, DATA) \
\
using namespace Jagerts::Kaleid::Math; \
using namespace Jagerts::Kaleid::Graphics; \
using namespace Jagerts::Kaleid::Game; \
using namespace Jagerts::Felcp::Helpers; \
\
Mesh* CLASS::_s_mesh = NULL; \
std::vector<RenderableShape*> CLASS::_shapes = std::vector<RenderableShape*>(); \
\
CLASS::##CLASS##() \
{ \
	this->_mesh = CLASS::_s_mesh; \
	this->_shader_program = NULL; \
	this->_shapes.push_back(this); \
} \
\
CLASS::~##CLASS##() \
{ \
	VectorHelper::RemoveItem(CLASS::_shapes, (RenderableShape*)this); \
} \
 \
bool CLASS::MeshExists() \
{ \
	return CLASS::_s_mesh != NULL; \
} \
 \
Mesh* CLASS::CreateMesh(GraphicsFactory*& graphics_factory) \
{ \
	if (CLASS::_s_mesh == NULL) \
	{ \
		DATA; \
		CLASS::_s_mesh = mesh; \
		CLASS::_s_mesh->Compose(); \
		 \
		for (RenderableShape*& shape : CLASS::_shapes) \
			shape->_mesh = CLASS::_s_mesh; \
	} \
 \
	return CLASS::GetMesh(); \
} \
\
Mesh* CLASS::GetMesh() \
{ \
	return CLASS::_s_mesh; \
} \
\
void CLASS::FreeMesh(GraphicsFactory*& graphics_factory) \
{ \
	graphics_factory->FreeIndexBuffer(CLASS::_s_mesh->GetIndexBuffer()); \
	graphics_factory->FreeVertexBuffers(CLASS::_s_mesh->GetVertexBuffers()); \
	graphics_factory->FreeMesh(CLASS::_s_mesh); \
 \
	for (RenderableShape*& shape : CLASS::_shapes) \
		shape->_mesh = NULL; \
} \

#endif