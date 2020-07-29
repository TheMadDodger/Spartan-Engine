#include "stdafx.h"
#include "AIComponent.h"

namespace Spartan
{
	AIComponent::AIComponent() : m_pAIBehaviour(nullptr), BaseComponent("AI Agent")
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

	void AIComponent::Initialize(const GameContext&)
	{
		if (m_pAIBehaviour)
		{
			m_pAIBehaviour->SetOwner(this);
			m_pAIBehaviour->Initialize();
		}
	}

	void AIComponent::Update(const GameContext& gameContext)
	{
		if (m_pAIBehaviour) m_pAIBehaviour->Tick(gameContext.pTime->GetDeltaTime() / 1000.0f);
	}
}