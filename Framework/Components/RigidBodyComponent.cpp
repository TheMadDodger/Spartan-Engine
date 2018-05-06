#include "stdafx.h"
#include "../../stdafx.h"
#include "RigidBodyComponent.h"
#include "../Scenes/GameObject.h"
#include "../Scenes/GameScene.h"

RigidBodyComponent::RigidBodyComponent(const Vector2 &bodyPivot) : m_BodyPivot(bodyPivot)
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
	//ZeroMemory(&bodyDef, sizeof(b2BodyDef));
	bodyDef.position.Set(m_BodyPivot.x, m_BodyPivot.y);
	bodyDef.type = b2_dynamicBody;
	m_Body = physicsWorld->CreateBody(&bodyDef);
}
