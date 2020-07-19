#pragma once
#include "Node.h"

namespace Spartan
{
	enum class BTNodeResult
	{
		BTNotStarted,
		BTInProgress,
		BTSucces,
		BTFailed,
		BTAbort,
	};

	class BTNode : Node
	{
	public:
		BTNode();
		virtual ~BTNode();

		virtual void ExecuteNode() = 0;
		BTNodeResult RootExecuteNode();

		virtual void TickNode(float) {};
		virtual BTNodeResult RootTickNode(float deltaTime);

		AIBehaviourTree* GetBehaviourTree();
		const BTNodeResult& GetNodeState() const;

		bool HasExecuted();
		void FullReset();

	protected:
		void RootResetNode();
		virtual void ResetNode() {};

	protected:
		// The current task being executed
		int m_CurrentNode = -1;
		BTNode* m_pCurrentNode;

		// Execute only gets called once on the first tick
		bool m_bExecuted = false;

		// Attached nodes
		vector<BTNode*> m_pNodes;

		// The behaviour tree that owns this node
		AIBehaviourTree* m_pOwnerTree;

		// The state of the node
		BTNodeResult m_NodeState = BTNodeResult::BTNotStarted;

	private:
		friend class AIBehaviourTree;
		void SetBehaviourTree(AIBehaviourTree* pBehaviourTree);
	};

	class BTTaskNode : public BTNode
	{
	public:
		BTTaskNode() {};
		virtual ~BTTaskNode() {};

	private:
		virtual void RootExecuteTask(Blackboard* pBlackboard);

		virtual void ExecuteNode() override;

		virtual void TickNode(float deltaTime) override;

		virtual BTNodeResult ExecuteTask(Blackboard*) = 0;
		virtual void TickTask(float, Blackboard*) {};

		// Events
		virtual void OnTaskAborted() {};
		virtual void OnTaskFinished() {};

	protected:
		void FinishTask(const BTNodeResult& result);

	private:
		friend class BTTreeNode;
	};

	class BTTreeNode : public BTNode
	{
	public:
		BTTreeNode() {};
		virtual ~BTTreeNode() {};

		void AddNode(BTNode* pNode);

	protected:
		const BTNodeResult& GetCurrentNodeState() const;

		bool NextNode();
	};

	class BTTreeRootNode : public BTTreeNode
	{
	public:
		BTTreeRootNode() {};
		virtual ~BTTreeRootNode() {};

	private:
		virtual void ExecuteNode() {};
		virtual void TickNode(float deltaTime) override;
	};

	class BTTreeSelectorNode : public BTTreeNode
	{
	public:
		BTTreeSelectorNode() {};
		virtual ~BTTreeSelectorNode() {};

	private:
		virtual void ExecuteNode() {};
		virtual void TickNode(float deltaTime) override;
	};

	class BTTreeSequenceNode : public BTTreeNode
	{
	public:
		BTTreeSequenceNode() {};
		virtual ~BTTreeSequenceNode() {};

	private:
		virtual void ExecuteNode() {};
		virtual void TickNode(float deltaTime) override;
	};
}