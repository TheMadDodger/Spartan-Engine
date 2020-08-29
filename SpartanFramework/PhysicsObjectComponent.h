#pragma once
#include "BaseComponent.h"
#include "btBulletDynamicsCommon.h"
#include "3DColliders.h"

namespace Spartan
{
	class PhysicsObjectComponent : public BaseComponent, public btMotionState
	{
	public:
		PhysicsObjectComponent();
		~PhysicsObjectComponent();

		COMPONENT(PhysicsObjectComponent);

		void SetCollider(Collider3D* pCollider);
		void SetMass(float mass);

		void ApplyForce(const Spartan::Vector3& force, const Spartan::Vector3& relativePos);
		void ClearForce();
		void SetGravity(const Spartan::Vector3& gravity);
		void SetFriction(float friction);
		void SetRestitution(float restitution);

		Vector3 GetLinearVelocity();

		void UpdateTransform(const Spartan::Vector3& position, const Spartan::Quaternion& rotation, const Spartan::Vector3& scale);

		btRigidBody* GetbtRigidBody();
		Collider3D* GetCollider();

	private:
		void Initialize(const GameContext& gameContext) override;

		// Motion state functions
		void getWorldTransform(btTransform& worldTrans) const override;
		void setWorldTransform(const btTransform& worldTrans) override;

	private:
		btRigidBody* m_pCollisionObject;
		Collider3D* m_pCollider;

		float m_Mass;
		float m_Friction;
		float m_Restitution;
		btVector3 m_LocalInertia;
	};
}