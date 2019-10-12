#include "stdafx.h"
#include "ParticleComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"

ParticleComponent::ParticleComponent() : m_pEmitter(nullptr), m_pSystem(nullptr), BaseComponent("Particle Emitter")
{
}

ParticleComponent::~ParticleComponent()
{
}

void ParticleComponent::Initialize(const GameContext &gameContext)
{
	m_pSystem = gameContext.pParticleManager->CreateParticleSystem();
	m_Settings.Position = GetGameObject()->GetTransform()->GetWorldPosition();
	m_pEmitter = m_pSystem->CreateEmitter(m_Settings);

	m_pSystem->SetCamera(GetGameObject()->GetGameScene()->GetActiveCamera());
}

void ParticleComponent::Update(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	m_pSystem->SetCamera(GetGameObject()->GetGameScene()->GetActiveCamera());

	m_Settings.Position = GetGameObject()->GetTransform()->GetWorldPosition();
	m_pEmitter->UpdateSettings(m_Settings);
}
