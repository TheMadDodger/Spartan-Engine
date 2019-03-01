#pragma once
#include "BehaviourTree.h"
#include "Blackboard.h"
#include "stdafx.h"

enum BTNodeResult
{
	BTInProgress,
	BTSucces,
	BTFailed,
	BTAbort,
};

class BTNode
{
public:
	BTNode() {};
	virtual ~BTNode()
	{
		for (BTNode *pNode : m_pNodes)
		{
			delete pNode;
		}
		m_pNodes.clear();
	}

	virtual void ExecuteNode() = 0;

	BTNodeResult RootExecuteNode()
	{
		ExecuteNode();

		return m_NodeState;
	}

	virtual void TickNode() {};

	virtual BTNodeResult RootTickNode()
	{

		return m_NodeState;
	}

	BehaviourTree *GetBehaviourTree()
	{
		return m_pOwnerTree;
	}

	const BTNodeResult &GetNodeState() const
	{
		return m_NodeState;
	}

protected:
	void RootResetNode()
	{
		m_pCurrentNode = nullptr;
		m_CurrentNode = 0;
		m_bFailed = false;
		ResetNode();
	}

	virtual void ResetNode() {};

protected:
	// The current task being executed
	unsigned int m_CurrentNode = 0;
	BTNode *m_pCurrentNode;

	// When the node fails this flag is set
	bool m_bFailed = false;

	// Attached nodes
	vector<BTNode*> m_pNodes;

	// The behaviour tree that owns this node
	BehaviourTree *m_pOwnerTree;

	// The state of the node
	BTNodeResult m_NodeState;
};
//
//class BTRootNode : public BTNode
//{
//public:
//	BTRootNode() {};
//	virtual ~BTRootNode() {};
//
//	virtual BTNodeResult ExecuteNode() = 0;
//	virtual BTNodeResult TickNode() {};
//};

class BTTaskNode : public BTNode
{
public:
	BTTaskNode() {};
	virtual ~BTTaskNode() {};

private:
	virtual void RootExecuteTask(Blackboard *pBlackboard)
	{
		m_NodeState = ExecuteTask(pBlackboard);
		m_bExecuted = true;
		return;
	}

	virtual void TickNode() override
	{
		Blackboard *pBlackboard = GetBehaviourTree()->GetBlackboard();
		TickTask(pBlackboard);
	}

	virtual BTNodeResult ExecuteTask(Blackboard *) = 0;
	virtual void TickTask(Blackboard *) {};

	// Events
	virtual void OnTaskAborted() {};
	virtual void OnTaskFinished() {};

protected:
	void FinishTask(const BTNodeResult &result)
	{
		m_NodeState = result;
	}

private:
	virtual void ResetNode() override
	{
		m_bExecuted = false;
	}

private:
	friend class BTTreeNode;
	bool m_bExecuted = false;
};

class BTTreeNode : public BTNode
{
public:
	BTTreeNode() {};
	virtual ~BTTreeNode() {};

	void AddNode(BTNode *pNode)
	{
		m_pNodes.push_back(pNode);
	}

protected:

	const BTNodeResult &GetCurrentNodeState() const
	{
		return m_pCurrentNode->GetNodeState();
	}

	bool StartNextNode()
	{
		++m_CurrentNode;
		if (m_CurrentNode >= m_pNodes.size())
		{
			m_CurrentNode = 0;
			return true;
		}

		m_pCurrentNode = m_pNodes[m_CurrentNode];
	}

private:
	/*void Start()
	{
		if (m_pNodes.size() <= 0)
		{
			m_CurrentNode = 0;
			m_pCurrentNode = nullptr;
			return;
		}

		m_pCurrentNode = m_pNodes[0];
	}*/

	/*BTNodeResult RootTickNode()
	{
		// No attached nodes
		if (m_pCurrentNode == nullptr) return BTNodeResult::BTSucces;

		m_pCurrentNode->RootTickNode();
		return TickNode();
	}*/
};

class BTTreeSelectorNode : public BTTreeNode
{
public:
	BTTreeSelectorNode() {};
	virtual ~BTTreeSelectorNode() {};

private:
	virtual void TickNode() override
	{
		BTNodeResult state = GetCurrentNodeState();
		if (state == BTNodeResult::BTFailed)
		{
			if (StartNextTask() && m_bFailed)
			{
				m_NodeState = m_bFailed ? BTNodeResult::BTFailed : BTNodeResult::BTSucces;
			}

			m_NodeState = BTNodeResult::BTInProgress;
		}
		else if (state == BTNodeResult::BTSucces)
		{
			m_NodeState = BTNodeResult::BTSucces;
		}
	}
};

class BTTreeSequenceNode : public BTTreeNode
{
public:
	BTTreeSequenceNode() {};
	virtual ~BTTreeSequenceNode() {};

	virtual void TickNode() override
	{
		BTNodeResult state = GetCurrentNodeState();
		if (state == BTNodeResult::BTSucces)
		{
			if (StartNextTask())
			{
				m_NodeState = BTNodeResult::BTSucces;
				return;
			}

			m_NodeState = BTNodeResult::BTInProgress;
			return;
		}

		m_NodeState = state;
	}
};