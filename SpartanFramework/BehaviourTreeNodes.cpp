#include "stdafx.h"
#include "BehaviourTreeNodes.h"

namespace Spartan
{
	BTNode::BTNode() : m_pOwnerTree(nullptr)
	{
	}

	BTNode::~BTNode()
	{
		for (BTNode* pNode : m_pNodes)
		{
			delete pNode;
		}
		m_pNodes.clear();
	}

	BTNodeResult BTNode::RootExecuteNode()
	{
		ExecuteNode();
		m_bExecuted = true;

		return m_NodeState;
	}

	BTNodeResult BTNode::RootTickNode(float deltaTime)
	{
		TickNode(deltaTime);

		return m_NodeState;
	}

	AIBehaviourTree* BTNode::GetBehaviourTree()
	{
		return m_pOwnerTree;
	}

	const BTNodeResult& BTNode::GetNodeState() const
	{
		return m_NodeState;
	}

	bool BTNode::HasExecuted()
	{
		return m_bExecuted;
	}

	void BTNode::FullReset()
	{
		for (BTNode* pNode : m_pNodes)
		{
			pNode->FullReset();
		}

		RootResetNode();
	}

	void BTNode::RootResetNode()
	{
		m_pCurrentNode = nullptr;
		m_CurrentNode = -1;
		m_bExecuted = false;
		m_NodeState = BTNodeResult::BTNotStarted;
		ResetNode();
	}

	void BTNode::SetBehaviourTree(AIBehaviourTree* pBehaviourTree)
	{
		if (!m_pOwnerTree) m_pOwnerTree = pBehaviourTree;

		for (BTNode* pNode : m_pNodes)
		{
			pNode->SetBehaviourTree(pBehaviourTree);
		}
	}

	void BTTaskNode::RootExecuteTask(Blackboard* pBlackboard)
	{
		m_NodeState = ExecuteTask(pBlackboard);
		return;
	}

	void BTTaskNode::ExecuteNode()
	{
		Blackboard* pBlackboard = GetBehaviourTree()->GetBlackboard();
		m_NodeState = ExecuteTask(pBlackboard);
	}

	void BTTaskNode::TickNode(float deltaTime)
	{
		Blackboard* pBlackboard = GetBehaviourTree()->GetBlackboard();
		TickTask(deltaTime, pBlackboard);
	}

	void BTTaskNode::FinishTask(const BTNodeResult& result)
	{
		m_NodeState = result;
	}

	void BTTreeNode::AddNode(BTNode* pNode)
	{
		m_pNodes.push_back(pNode);
	}

	const BTNodeResult& BTTreeNode::GetCurrentNodeState() const
	{
		return m_pCurrentNode->GetNodeState();
	}

	bool BTTreeNode::NextNode()
	{
		++m_CurrentNode;
		if (m_CurrentNode >= (int)m_pNodes.size())
		{
			m_CurrentNode = -1;
			return true;
		}

		m_pCurrentNode = m_pNodes[m_CurrentNode];
		return false;
	}

	void BTTreeRootNode::TickNode(float deltaTime)
	{
		BTNodeResult state;

		if (m_CurrentNode == -1) NextNode();
		if (m_pCurrentNode->HasExecuted()) state = m_pCurrentNode->RootTickNode(deltaTime);
		else state = m_pCurrentNode->RootExecuteNode();

		if (state == BTNodeResult::BTFailed || state == BTNodeResult::BTAbort)
		{
			if (NextNode())
			{
				FullReset();
				return;
			}

			m_NodeState = BTNodeResult::BTInProgress;
			return;
		}
		else if (state == BTNodeResult::BTSucces)
		{
			FullReset();
			return;
		}

		m_NodeState = state;
	}

	void BTTreeSelectorNode::TickNode(float deltaTime)
	{
		BTNodeResult state;

		if (m_CurrentNode == -1) NextNode();
		if (m_pCurrentNode->HasExecuted()) state = m_pCurrentNode->RootTickNode(deltaTime);
		else state = m_pCurrentNode->RootExecuteNode();

		if (state == BTNodeResult::BTFailed)
		{
			if (NextNode())
			{
				m_NodeState = BTNodeResult::BTFailed;
				return;
			}

			m_NodeState = BTNodeResult::BTInProgress;
			return;
		}

		m_NodeState = state;
	}

	void BTTreeSequenceNode::TickNode(float deltaTime)
	{
		BTNodeResult state;

		if (m_CurrentNode == -1) NextNode();
		if (m_pCurrentNode->HasExecuted()) state = m_pCurrentNode->RootTickNode(deltaTime);
		else state = m_pCurrentNode->RootExecuteNode();

		if (state == BTNodeResult::BTSucces)
		{
			if (NextNode())
			{
				m_NodeState = BTNodeResult::BTSucces;
				return;
			}

			m_NodeState = BTNodeResult::BTInProgress;
			return;
		}

		m_NodeState = state;
	}
}