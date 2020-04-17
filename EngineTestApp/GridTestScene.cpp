#include "stdafx.h"
#include "GridTestScene.h"
#include "FreeCamera.h"
#include <Grid.h>
#include <GridComponent.h>
#include <CameraComponent.h>
#include <AStarPathFinding.h>
#include <PathFindingNodes.h>
#include <InputManager.h>

GridTestScene::GridTestScene() : GameScene("Grid Test Scene")
{
}

GridTestScene::~GridTestScene()
{
	delete m_pAStarPathFinding;
	m_pAStarPathFinding = nullptr;
}

void GridTestScene::Initialize(const GameContext & gameContext)
{
	gameContext.pInput->AddInputAction(InputAction("Findpath", InputType::Pressed, 'f'));
	m_pCamera = Instantiate<FreeCamera>();

	Grid2D *pGrid = new Grid2D(60, 60, Vector2(10.0f, 10.0f));
	pGrid->Generate<AStar2DGridNode>();

	for (size_t i = 0; i < 250; i++)
	{
		Vector2 randomCoord = RandomRangeVector2(Vector2::Zero(), Vector2(60.0f, 60.0f));
		IntVector2 randCoord;
		randCoord.x = (int)randomCoord.x;
		randCoord.y = (int)randomCoord.y;
		auto pNode = pGrid->GetNode(randCoord);
		auto pPathNode = dynamic_cast<IAStarPathNode*>(pNode);
		pPathNode->SetMoveable(false);
	}

	GameObject* pGridObject = Instantiate<GameObject>();
	m_pGrid = pGridObject->CreateRuntimeComponent<GridComponent>();
	m_pGrid->SetGrid(pGrid);

	m_pAStarPathFinding = new AStarPathFinding(pGrid);

	SetEnabled(true);
}

void GridTestScene::PostInitialize(const GameContext & gameContext)
{
	auto pCam = m_pCamera->GetComponent<CameraComponent>();
	SetActiveCamera(pCam);
}

void GridTestScene::Update(const GameContext &gameContext)
{
	/*if (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		auto worldClick = gameContext.pInput->GetMouseWorldPosition((Matrix3X3&)GetActiveCamera()->GetCameraMatrix());
		m_pStartNode = m_pGrid->GetGrid()->GetNodeAtWorldPosition(worldClick);
		AStarPathFinding::m_SelectedNode = m_pStartNode;
	}

	if (gameContext.pInput->IsMouseButtonDown(SDL_BUTTON_RIGHT))
	{
		auto worldClick = gameContext.pInput->GetMouseWorldPosition((Matrix3X3&)GetActiveCamera()->GetCameraMatrix());
		m_pEndNode = m_pGrid->GetGrid()->GetNodeAtWorldPosition(worldClick);
		AStarPathFinding::m_SelectedNode = m_pEndNode;
	}

	if (gameContext.pInput->IsActionTriggered("Findpath"))
	{
		if (m_pStartNode == nullptr || m_pEndNode == nullptr) return;
		m_pAStarPathFinding->FindPath(m_pStartNode, m_pEndNode);
	}*/
}

void GridTestScene::Draw(const GameContext &gameContext)
{
}
