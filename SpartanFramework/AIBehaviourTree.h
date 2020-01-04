#pragma once

class Blackboard;
class BTNode;

class AIBehaviourTree : public BaseAIBehaviour
{
public:
	AIBehaviourTree(BTNode *pRootNode);
	virtual ~AIBehaviourTree();

	Blackboard *GetBlackboard();

private:
	virtual void Initialize() override;
	virtual void Tick(float deltaTime) override;

private:
	Blackboard *m_pBlackboard;
	BTNode *m_pRootNode;
};
