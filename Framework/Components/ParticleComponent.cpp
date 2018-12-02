#include "stdafx.h"
#include "../../stdafx.h"
#include "ParticleComponent.h"
#include "TransformComponent.h"
#include "../Scenes/GameObject.h"
#include "../Scenes/GameScene.h"

ParticleComponent::ParticleComponent(const EmitterSettings &settings) : m_Settings(settings), BaseComponent("Particle Emitter")
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
