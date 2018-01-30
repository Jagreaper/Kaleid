#pragma once

#include "Jagerts.Kaleid.Graphics/RenderableShape.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class JAGERTS_KALEID_GRAPHICS_API Cube : public RenderableShape
	{
	public:
		Cube();
		~Cube();
		jkgUsingRenderableShape;
		jkmUsingTransformableObject;
		jkgRenderableShapeStaticHeader;
	};
}