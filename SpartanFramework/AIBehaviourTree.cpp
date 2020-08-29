#include "stdafx.h"
#include "AIBehaviourTree.h"
#include "BehaviourTreeNodes.h"

namespace Spartan
{
	AIBehaviourTree::AIBehaviourTree(BTNode* pRootNode) : m_pRootNode(pRootNode), m_pBlackboard(new Blackboard())
	{
	}

	AIBehaviourTree::AIBehaviourTree()
	{
	}

	AIBehaviourTree::~AIBehaviourTree()
	{
		delete m_pRootNode;
		m_pRootNode = nullptr;

		delete m_pBlackboard;
		m_pBlackboard = nullptr;
	}

	Blackboard* AIBehaviourTree::GetBlackboard()
	{
		return m_pBlackboard;
	}

	void AIBehaviourTree::Initialize()
	{
		m_pRootNode->SetBehaviourTree(this);
		m_pRootNode->FullReset();
	}

	void AIBehaviourTree::Tick(float deltaTime)
	{
		m_pRootNode->RootTickNode(deltaTime);
	}
}