#pragma once
#include "BaseComponent.h"
#include "btBulletDynamicsCommon.h"
#include "3DColliders.h"

namespace SpartanEngine
{
	class PhysicsObjectComponent : public BaseComponent, public btMotionState
	{
	public:
		PhysicsObjectComponent();
		~PhysicsObjectComponent();

		void SetCollider(Collider3D* pCollider);
		void SetMass(float mass);

	private:
		void Initialize(const GameContext& gameContext) override;

		// Motion state functions
		void getWorldTransform(btTransform& worldTrans) const override;
		void setWorldTransform(const btTransform& worldTrans) override;

	private:
		COMPONENT_EDITOR(PhysicsObjectComponent);

		btRigidBody* m_pCollisionObject;
		Collider3D* m_pCollider;

		float m_Mass;
		btVector3 m_LocalInertia;
	};
}