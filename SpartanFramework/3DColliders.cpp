#include "stdafx.h"
#include "3DColliders.h"

namespace Spartan
{
	Collider3D::Collider3D(btCollisionShape* pShape) : m_pCollisionShape(pShape) {}

	Collider3D::~Collider3D()
	{
		if (m_pCollisionShape) delete m_pCollisionShape;
		m_pCollisionShape = nullptr;
	}

	Box::Box(const Math::Vector3& dimensions) : m_Dimensions(dimensions), Collider3D(new btBoxShape(Math::TobtVector3(dimensions))) {}
	Box::~Box() {}

	Sphere::Sphere(float radius) : m_Radius(radius), Collider3D(new btSphereShape((btScalar)radius)) {}
	Sphere::~Sphere() {}
	
	InfinitePlane::InfinitePlane(const Vector3& up, float planeConstraint) : m_Up(up), m_PlaneConstraint(planeConstraint),
		Collider3D(new btStaticPlaneShape(TobtVector3(up), planeConstraint)) {}

	InfinitePlane::~InfinitePlane() {}
}