#include "stdafx.h"
#include "Collider2DComponent.h"
#include "RigidBody2DComponent.h"
#include "GameObject.h"
#include "GameScene.h"

namespace Spartan
{
	Collider2DComponent::Collider2DComponent() :
		m_pCollider(nullptr), BaseComponent("Collider 2D"), m_PhysicsMaterial(PhysicsMaterial())
	{
	}

	Collider2DComponent::~Collider2DComponent()
	{
		if (m_pCollider)
		{
			delete m_pCollider;
			m_pCollider = nullptr;
		}
	}

	void Collider2DComponent::SetCollider(Collider2D* newCollider)
	{
		m_pCollider = newCollider;
	}

	void Collider2DComponent::UpdateCollider(Collider2D* newCollider)
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

		auto pRigid = GetGameObject()->GetComponent<RigidBody2DComponent>();
		pRigid->Getb2Body()->DestroyFixture(m_pFixture);
		m_pFixture = pRigid->Getb2Body()->CreateFixture(&m_FixtureDef);
	}

	void Collider2DComponent::Initialize(const GameContext& gameContext)
	{
		if (!m_pCollider) return;

		UNREFERENCED_PARAMETER(gameContext);
		auto pRigid = GetGameObject()->GetComponent<RigidBody2DComponent>();
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

	void Collider2DComponent::Draw(const GameContext& gameContext)
	{
		if (!m_pCollider) return;
		if (Utilities::Debug::CanRenderDebug())
		{
			m_pCollider->DrawDebugShape(gameContext);
		}
	}
}