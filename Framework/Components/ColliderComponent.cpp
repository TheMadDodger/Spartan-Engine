#include "stdafx.h"
#include "../../stdafx.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "../Scenes/GameObject.h"
#include "../Scenes/GameScene.h"

ColliderComponent::ColliderComponent(Collider *collider) : m_pCollider(collider)
{
}

ColliderComponent::~ColliderComponent()
{
	delete m_pCollider;
	m_pCollider = nullptr;
}

void ColliderComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	auto pRigid = GetGameObject()->GetComponent<RigidBodyComponent>();
	if (!pRigid)
	{
		Utilities::Debug::LogError("ColliderComponent::Initialize > ColliderComponent needs a RigidBodyComponent in order to function!");
		return;
	}

	m_FixtureDef.shape = m_pCollider->ApplyShape();
	m_FixtureDef.density = 1.0f;
	m_FixtureDef.friction = 0.3f;

	m_pFixture = pRigid->Getb2Body()->CreateFixture(&m_FixtureDef);
}

void ColliderComponent::Draw(const GameContext &gameContext)
{
	if (Utilities::Debug::CanRenderDebug())
	{
		glPushMatrix();
		GetGameObject()->GetTransform()->ApplyTransform();
		m_pCollider->DrawDebugShape(gameContext);
		glPopMatrix();
	}
}
