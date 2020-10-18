#include "stdafx.h"
//#include "BehaviourTreeTestScene.h"
//#include <GameObject.h>
//#include <AI.h>
//#include <Tasks.h>
//
//BehaviourTreeTestScene::BehaviourTreeTestScene() : Spartan::GameScene("Behaviour Tree Test Scene")
//{
//}
//
//BehaviourTreeTestScene::~BehaviourTreeTestScene()
//{
//}
//
//void BehaviourTreeTestScene::Initialize(const Spartan::GameContext &)
//{
//	Spartan::GameObject *pAIObject = Instantiate<Spartan::GameObject>();
//
//	Spartan::BTTreeRootNode *pRootNode = new Spartan::BTTreeRootNode();
//
//	Spartan::BTTreeSequenceNode *pSelectorNode = new Spartan::BTTreeSequenceNode();
//	pRootNode->AddNode(pSelectorNode);
//
//	Spartan::BTTaskNode *pWaitTask = new Spartan::BTWaitTask();
//	pSelectorNode->AddNode(pWaitTask);
//
//	pWaitTask = new Spartan::BTWaitTask(10.0f);
//	pSelectorNode->AddNode(pWaitTask);
//
//	Spartan::AIBehaviourTree *pBehaviourTree = new Spartan::AIBehaviourTree(pRootNode);
//	pAIObject->CreateRuntimeComponent<Spartan::AIComponent>()->SetBehaviour(pBehaviourTree);
//}
//
//void BehaviourTreeTestScene::Update(const Spartan::GameContext &)
//{
//}
//
//void BehaviourTreeTestScene::Draw(const Spartan::GameContext &)
//{
//}
