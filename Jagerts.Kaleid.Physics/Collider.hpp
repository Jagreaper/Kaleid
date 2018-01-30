#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/Transform.hpp"
#include "Jagerts.Kaleid.Geometry/Line.hpp"

class JAGERTS_KALEID_PHYSICS_API Collider : Jagerts::Kaleid::Math::TransformableObject
{
public:
	virtual bool Intersects(Collider* const collider) = 0;
	virtual bool Intersects(Collider* const& collider) = 0;
	virtual bool Intersects(const Jagerts::Kaleid::Math::Vector3F point) = 0;
	virtual bool Intersects(const Jagerts::Kaleid::Math::Vector3F& point) = 0;
	virtual bool Intersects(const Jagerts::Kaleid::Geometry::VectorLineF line) = 0;
	virtual bool Intersects(const Jagerts::Kaleid::Geometry::VectorLineF& line) = 0;
	jkmUsingTransformableObject;
private:
};