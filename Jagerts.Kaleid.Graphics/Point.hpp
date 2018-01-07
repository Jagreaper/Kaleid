#pragma once

#include "RenderableShape.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class JAGERTS_KALEID_GRAPHICS_API Point : public RenderableShape
	{
	public:
		Point();
		~Point();
		jkgUsingRenderableShape;
		jkmUsingTransformableObject;
		jkgRenderableShapeStaticHeader;
	};
}