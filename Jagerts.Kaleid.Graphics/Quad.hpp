#pragma once

#include "RenderableShape.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class JAGERTS_KALEID_GRAPHICS_API Quad : public RenderableShape
	{
	public:
		Quad();
		~Quad();
		jkgUsingRenderableShape;
		jkmUsingTransformableObject;
		jkgRenderableShapeStaticHeader;
	};
}