#pragma once
#include "BaseAIBehaviour.h"
#include "Blackboard.h"

namespace Spartan
{
	class BTNode;

	class AIBehaviourTree : public BaseAIBehaviour
	{
	public:
		AIBehaviourTree(BTNode* pRootNode);
		AIBehaviourTree();
		virtual ~AIBehaviourTree();

		Blackboard* GetBlackboard();

		BASIC_OBJECT(AIBehaviourTree, BaseAIBehaviour);

	private:
		virtual void Initialize() override;
		virtual void Tick(float deltaTime) override;

	private:
		Blackboard* m_pBlackboard;
		BTNode* m_pRootNode;
	};
}