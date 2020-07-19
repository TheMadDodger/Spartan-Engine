#include "stdafx.h"
//#include "GridTestScene.h"
//#include "FreeCamera.h"
//#include <Grid.h>
//#include <GridComponent.h>
//#include <CameraComponent.h>
//#include <AStarPathFinding.h>
//#include <PathFindingNodes.h>
//#include <InputManager.h>
//
//GridTestScene::GridTestScene() : Spartan::GameScene("Grid Test Scene")
//{
//}
//
//GridTestScene::~GridTestScene()
//{
//	delete m_pAStarPathFinding;
//	m_pAStarPathFinding = nullptr;
//}
//
//void GridTestScene::Initialize(const Spartan::GameContext & gameContext)
//{
//	gameContext.pInput->AddInputAction(Spartan::InputAction("Findpath", Spartan::InputType::Pressed, 'f'));
//	m_pCamera = Instantiate<FreeCamera>();
//
//	Spartan::Grid2D *pGrid = new Spartan::Grid2D(60, 60, Spartan::Vector2(10.0f, 10.0f));
//	pGrid->Generate<Spartan::AStar2DGridNode>();
//
//	for (size_t i = 0; i < 250; i++)
//	{
//		Spartan::Vector2 randomCoord = Spartan::RandomRangeVector2(Spartan::Vector2::Zero(), Spartan::Vector2(60.0f, 60.0f));
//		Spartan::IntVector2 randCoord;
//		randCoord.x = (int)randomCoord.x;
//		randCoord.y = (int)randomCoord.y;
//		auto pNode = pGrid->GetNode(randCoord);
//		auto pPathNode = dynamic_cast<Spartan::IAStarPathNode*>(pNode);
//		pPathNode->SetMoveable(false);
//	}
//
//	Spartan::GameObject* pGridObject = Instantiate<Spartan::GameObject>();
//	m_pGrid = pGridObject->CreateRuntimeComponent<Spartan::GridComponent>();
//	m_pGrid->SetGrid(pGrid);
//
//	m_pAStarPathFinding = new Spartan::AStarPathFinding(pGrid);
//
//	SetEnabled(true);
//}
//
//void GridTestScene::PostInitialize(const Spartan::GameContext & gameContext)
//{
//	auto pCam = m_pCamera->GetComponent<Spartan::CameraComponent>();
//	SetActiveCamera(pCam);
//}
//
//void GridTestScene::Update(const Spartan::GameContext &gameContext)
//{
//	/*if (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_LEFT))
//	{
//		auto worldClick = gameContext.pInput->GetMouseWorldPosition((Matrix3X3&)GetActiveCamera()->GetCameraMatrix());
//		m_pStartNode = m_pGrid->GetGrid()->GetNodeAtWorldPosition(worldClick);
//		AStarPathFinding::m_SelectedNode = m_pStartNode;
//	}
//
//	if (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_RIGHT))
//	{
//		auto worldClick = gameContext.pInput->GetMouseWorldPosition((Matrix3X3&)GetActiveCamera()->GetCameraMatrix());
//		m_pEndNode = m_pGrid->GetGrid()->GetNodeAtWorldPosition(worldClick);
//		AStarPathFinding::m_SelectedNode = m_pEndNode;
//	}
//
//	if (gameContext.pInput->IsActionTriggered("Findpath"))
//	{
//		if (m_pStartNode == nullptr || m_pEndNode == nullptr) return;
//		m_pAStarPathFinding->FindPath(m_pStartNode, m_pEndNode);
//	}*/
//}
//
//void GridTestScene::Draw(const Spartan::GameContext &gameContext)
//{
//}
