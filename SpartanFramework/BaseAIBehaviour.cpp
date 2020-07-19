#include "stdafx.h"
#include "BaseAIBehaviour.h"

namespace Spartan
{
	BaseAIBehaviour::BaseAIBehaviour()
	{
	}

	BaseAIBehaviour::~BaseAIBehaviour()
	{
	}

	AIComponent* BaseAIBehaviour::GetAIOwner()
	{
		return m_pAIOwner;
	}

	void BaseAIBehaviour::SetOwner(AIComponent* pOwner)
	{
		m_pAIOwner = pOwner;
	}
}