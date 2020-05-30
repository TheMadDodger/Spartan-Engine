#include "stdafx.h"
#include "BehaviourTreeTestScene.h"
#include <GameObject.h>
#include <AI.h>
#include <Tasks.h>

BehaviourTreeTestScene::BehaviourTreeTestScene() : SpartanEngine::GameScene("Behaviour Tree Test Scene")
{
}

BehaviourTreeTestScene::~BehaviourTreeTestScene()
{
}

void BehaviourTreeTestScene::Initialize(const SpartanEngine::GameContext &)
{
	SpartanEngine::GameObject *pAIObject = Instantiate<SpartanEngine::GameObject>();

	SpartanEngine::BTTreeRootNode *pRootNode = new SpartanEngine::BTTreeRootNode();

	SpartanEngine::BTTreeSequenceNode *pSelectorNode = new SpartanEngine::BTTreeSequenceNode();
	pRootNode->AddNode(pSelectorNode);

	SpartanEngine::BTTaskNode *pWaitTask = new SpartanEngine::BTWaitTask();
	pSelectorNode->AddNode(pWaitTask);

	pWaitTask = new SpartanEngine::BTWaitTask(10.0f);
	pSelectorNode->AddNode(pWaitTask);

	SpartanEngine::AIBehaviourTree *pBehaviourTree = new SpartanEngine::AIBehaviourTree(pRootNode);
	pAIObject->CreateRuntimeComponent<SpartanEngine::AIComponent>()->SetBehaviour(pBehaviourTree);
}

void BehaviourTreeTestScene::Update(const SpartanEngine::GameContext &)
{
}

void BehaviourTreeTestScene::Draw(const SpartanEngine::GameContext &)
{
}
