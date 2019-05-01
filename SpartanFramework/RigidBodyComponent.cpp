#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "ColliderComponent.h"

RigidBodyComponent::RigidBodyComponent(const b2BodyType &type, const Vector2 &bodyPivot) : m_BodyPivot(bodyPivot), m_BodyType(type), BaseComponent("Rigidbody")
{
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	auto physicsWorld = GetGameObject()->GetGameScene()->GetPhysicsWorld();
	b2BodyDef bodyDef;
	bodyDef.position.Set(m_BodyPivot.x, m_BodyPivot.y);
	bodyDef.type = m_BodyType;
	m_Body = physicsWorld->CreateBody(&bodyDef);
}

void RigidBodyComponent::Cleanup()
{
	auto pCol = GetGameObject()->GetComponent<ColliderComponent>();

	auto physicsWorld = GetGameObject()->GetGameScene()->GetPhysicsWorld();

	m_Body->DestroyFixture(pCol->m_pFixture);

	physicsWorld->DestroyBody(m_Body);
}
