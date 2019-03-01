#pragma once

class AIComponent;

class BaseAIBehaviour
{
public:
	BaseAIBehaviour();
	virtual ~BaseAIBehaviour();

	AIComponent *GetAIOwner();

	virtual void Initialize() = 0;
	virtual void Tick(float deltaTime) = 0;

private:
	AIComponent *m_pAIOwner;
};
