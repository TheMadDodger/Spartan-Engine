#include "stdafx.h"
#include "AIComponent.h"
#include "BaseAIBehaviour.h"

AIComponent::AIComponent() : m_pAIBehaviour(nullptr)
{
}

AIComponent::~AIComponent()
{
	if (m_pAIBehaviour)
	{
		delete m_pAIBehaviour;
		m_pAIBehaviour = nullptr;
	}
}

void AIComponent::SetBehaviour(BaseAIBehaviour* pBehaviour)
{
	m_pAIBehaviour = pBehaviour;
}

void AIComponent::Initialize(const GameContext &)
{
	if (m_pAIBehaviour)
	{
		m_pAIBehaviour->SetOwner(this);
		m_pAIBehaviour->Initialize();
	}
}

void AIComponent::Update(const GameContext &gameContext)
{
	if (m_pAIBehaviour) m_pAIBehaviour->Tick(gameContext.pTime->GetDeltaTime() / 1000.0f);
}
