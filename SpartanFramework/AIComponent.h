#pragma once
#include "BaseComponent.h"

class BaseAIBehaviour;

class AIComponent : public BaseComponent
{
public:
	COMPONENT_EDITOR(AIComponent)

	AIComponent(BaseAIBehaviour *pAIBehaviour);
	AIComponent() : m_pAIBehaviour(nullptr) {};
	virtual ~AIComponent();

private:
	virtual void Initialize(const GameContext &) override;
	virtual void Update(const GameContext &gameContext) override;

private:
	BaseAIBehaviour *m_pAIBehaviour;
};

