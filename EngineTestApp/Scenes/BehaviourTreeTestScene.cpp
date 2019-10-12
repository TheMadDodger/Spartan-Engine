#include "stdafx.h"
#include "BehaviourTreeTestScene.h"
#include <GameObject.h>
#include <AI.h>
#include <Tasks.h>

BehaviourTreeTestScene::BehaviourTreeTestScene() : GameScene("Behaviour Tree Test Scene")
{
}

BehaviourTreeTestScene::~BehaviourTreeTestScene()
{
}

void BehaviourTreeTestScene::Initialize(const GameContext &)
{
	GameObject *pAIObject = Instantiate<GameObject>();

	BTTreeRootNode *pRootNode = new BTTreeRootNode();

	BTTreeSequenceNode *pSelectorNode = new BTTreeSequenceNode();
	pRootNode->AddNode(pSelectorNode);

	BTTaskNode *pWaitTask = new BTWaitTask();
	pSelectorNode->AddNode(pWaitTask);

	pWaitTask = new BTWaitTask(10.0f);
	pSelectorNode->AddNode(pWaitTask);

	AIBehaviourTree *pBehaviourTree = new AIBehaviourTree(pRootNode);
	pAIObject->CreateRuntimeComponent<AIComponent>()->SetBehaviour(pBehaviourTree);
}

void BehaviourTreeTestScene::Update(const GameContext &)
{
}

void BehaviourTreeTestScene::Draw(const GameContext &)
{
}
