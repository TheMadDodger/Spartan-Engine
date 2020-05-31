#include "stdafx.h"
#include "RigidBody2DComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Collider2DComponent.h"

namespace SpartanEngine
{
	RigidBody2DComponent::RigidBody2DComponent() : BaseComponent("Rigidbody")
	{
	}

	RigidBody2DComponent::~RigidBody2DComponent()
	{
	}

	void RigidBody2DComponent::Initialize(const GameContext& gameContext)
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

	void RigidBody2DComponent::OnDestroy()
	{
		auto pCol = GetGameObject()->GetComponent<Collider2DComponent>();

		auto physicsWorld = GetGameObject()->GetGameScene()->GetPhysicsWorld();

		m_Body->DestroyFixture(pCol->m_pFixture);

		physicsWorld->DestroyBody(m_Body);
	}
}