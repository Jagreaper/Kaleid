#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"
#include "Jagerts.Kaleid.Graphics/Renderer.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class JAGERTS_KALEID_GRAPHICS_API Particle : public Jagerts::Kaleid::Graphics::RenderableObject, public Jagerts::Kaleid::Math::TransformableObject
	{
	public:
		jkmUsingTransformableObject;
		jkgRenderableObject;
		jkGetterSetterHeader(ShaderProgram, ShaderProgram* const);
	private:
		ShaderProgram* _shader_program = NULL;
	};
}