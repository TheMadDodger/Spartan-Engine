#pragma once
#include "stdafx.h"

namespace Spartan
{
	struct PhysicsMaterial
	{
		PhysicsMaterial()
			: Density(1.0f), Friction(1.0f), Restitution(0.1f), Filter(b2Filter()) {}

		PhysicsMaterial(float density, float friction, float restitution, const b2Filter& filter = b2Filter())
			: Density(density), Friction(friction), Restitution(restitution), Filter(filter) {}

		float Density;
		float Friction;
		float Restitution;
		b2Filter Filter;
	};
}