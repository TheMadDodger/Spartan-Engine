#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "ColliderComponent.h"

RigidBodyComponent::RigidBodyComponent() : BaseComponent("Rigidbody")
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

	auto pos = GetGameObject()->GetTransform()->Position;
	auto rot = GetGameObject()->GetTransform()->Rotation;

	Getb2Body()->SetTransform(Tob2Vec2(pos), rot.z);
}

void RigidBodyComponent::OnDestroy()
{
	auto pCol = GetGameObject()->GetComponent<ColliderComponent>();

	auto physicsWorld = GetGameObject()->GetGameScene()->GetPhysicsWorld();

	m_Body->DestroyFixture(pCol->m_pFixture);

	physicsWorld->DestroyBody(m_Body);
}
