#pragma once
#include "BaseAIBehaviour.h"
#include "Blackboard.h"

class BehaviourTree : public BaseAIBehaviour
{
public:
	BehaviourTree();
	virtual ~BehaviourTree();

	Blackboard *GetBlackboard() { return m_pBlackboard; };

private:
	Blackboard *m_pBlackboard;
};

