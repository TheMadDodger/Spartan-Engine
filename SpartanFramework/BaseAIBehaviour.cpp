#include "stdafx.h"
#include "BaseAIBehaviour.h"

BaseAIBehaviour::BaseAIBehaviour()
{
}

BaseAIBehaviour::~BaseAIBehaviour()
{
}

AIComponent *BaseAIBehaviour::GetAIOwner()
{
	return m_pAIOwner;
}
