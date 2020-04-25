#include "stdafx.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "GameScene.h"

namespace SpartanEngine
{
	ColliderComponent::ColliderComponent() :
		m_pCollider(nullptr), BaseComponent("Collider"), m_PhysicsMaterial(PhysicsMaterial())
	{
	}

	ColliderComponent::~ColliderComponent()
	{
		if (m_pCollider)
		{
			delete m_pCollider;
			m_pCollider = nullptr;
		}
	}

	void ColliderComponent::SetCollider(Collider* newCollider)
	{
		m_pCollider = newCollider;
	}

	void ColliderComponent::UpdateCollider(Collider* newCollider)
	{
		if (m_pCollider)
		{
			delete m_pCollider;
			m_pCollider = nullptr;
		}

		m_pCollider = newCollider;

		m_FixtureDef.shape = m_pCollider->ApplyShape();
		m_FixtureDef.density = m_PhysicsMaterial.Density;
		m_FixtureDef.friction = m_PhysicsMaterial.Friction;
		m_FixtureDef.restitution = m_PhysicsMaterial.Restitution;
		m_FixtureDef.filter = m_PhysicsMaterial.Filter;

		auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
		pRigid->Getb2Body()->DestroyFixture(m_pFixture);
		m_pFixture = pRigid->Getb2Body()->CreateFixture(&m_FixtureDef);
	}

	void ColliderComponent::Initialize(const GameContext& gameContext)
	{
		if (!m_pCollider) return;

		UNREFERENCED_PARAMETER(gameContext);
		auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
		if (!pRigid)
		{
			Utilities::Debug::LogError("ColliderComponent::Initialize > ColliderComponent needs a RigidBodyComponent in order to function!");
			return;
		}

		m_FixtureDef.shape = m_pCollider->ApplyShape();
		m_FixtureDef.density = m_PhysicsMaterial.Density;
		m_FixtureDef.friction = m_PhysicsMaterial.Friction;
		m_FixtureDef.restitution = m_PhysicsMaterial.Restitution;
		m_FixtureDef.filter = m_PhysicsMaterial.Filter;

		m_pFixture = pRigid->Getb2Body()->CreateFixture(&m_FixtureDef);
	}

	void ColliderComponent::Draw(const GameContext& gameContext)
	{
		if (!m_pCollider) return;
		if (Utilities::Debug::CanRenderDebug())
		{
			m_pCollider->DrawDebugShape(gameContext);
		}
	}
}