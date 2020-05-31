#include "stdafx.h"
#include "PhysicsObjectComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PhysicsProxy.h"

namespace SpartanEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent() : m_Mass(1.0f), m_pCollisionObject(nullptr),
		m_pCollider(nullptr), m_LocalInertia(0.0f, 0.0f, 0.0f) {}

	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
		if (m_pCollider) delete m_pCollider;
		if (m_pCollisionObject)
		{
			BaseGame::GetGame()->GetGameContext().pPhysicsProxy->RemoveCollisionObject(m_pCollisionObject);
			delete m_pCollisionObject;
		}

		m_pCollisionObject = nullptr;
		m_pCollider = nullptr;
	}

	void PhysicsObjectComponent::SetCollider(Collider3D* pCollider)
	{
		m_pCollider = pCollider;
	}

	void PhysicsObjectComponent::SetMass(float mass)
	{
		m_Mass = mass;
		m_LocalInertia = btVector3(0, 0, 0);
		
		if (m_pCollider && m_Mass != 0.0f)
			m_pCollider->m_pCollisionShape->calculateLocalInertia((btScalar)m_Mass, m_LocalInertia);

		if (m_pCollisionObject)
			m_pCollisionObject->setMassProps((btScalar)m_Mass, m_LocalInertia);
	}

	void PhysicsObjectComponent::Initialize(const GameContext& gameContext)
	{
		if (m_pCollider && m_Mass != 0.0f)
			m_pCollider->m_pCollisionShape->calculateLocalInertia((btScalar)m_Mass, m_LocalInertia);

		m_pCollisionObject = new btRigidBody((btScalar)m_Mass, this, m_pCollider->m_pCollisionShape, m_LocalInertia);
		gameContext.pPhysicsProxy->AddCollisionObject(m_pCollisionObject);
	}

	void PhysicsObjectComponent::getWorldTransform(btTransform& worldTrans) const
	{
		GetGameObject()->GetTransform()->BuildTransform();
		const Vector3& position = GetGameObject()->GetTransform()->GetWorldPosition();
		const Vector3& scale = GetGameObject()->GetTransform()->Scale;
		const Quaternion& rotation = GetGameObject()->GetTransform()->Rotation;
		worldTrans.setOrigin(TobtVector3(position));
		worldTrans.setRotation(TobtQuaternion(rotation));
		m_pCollider->m_pCollisionShape->setLocalScaling(TobtVector3(scale));
	}

	void PhysicsObjectComponent::setWorldTransform(const btTransform& worldTrans)
	{
		GetGameObject()->GetTransform()->SetWorldPosition(btToVector3(worldTrans.getOrigin()));
		GetGameObject()->GetTransform()->Rotation = btToQuaternion(worldTrans.getRotation());
	}
}