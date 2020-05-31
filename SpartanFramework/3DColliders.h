#pragma once

class btCollisionShape;

namespace SpartanEngine
{
	class Collider3D
	{
	protected:
		Collider3D(btCollisionShape* pShape);
		virtual ~Collider3D();

	private:
		friend class PhysicsObjectComponent;
		btCollisionShape* m_pCollisionShape;
	};

	class Box : public Collider3D
	{
	public:
		Box(const Math::Vector3& dimensions);
		virtual ~Box();

	private:
		Math::Vector3 m_Dimensions;
	};

	class Sphere : public Collider3D
	{
	public:
		Sphere(float radius);
		virtual ~Sphere();

	private:
		float m_Radius;
	};

	class InfinitePlane : public Collider3D
	{
	public:
		InfinitePlane(const Vector3& up = Vector3(0.0f, 1.0f, 0.0f), float planeConstraint = 0.0f);
		virtual ~InfinitePlane();

	private:
		Math::Vector3 m_Up;
		float m_PlaneConstraint;
	};
}