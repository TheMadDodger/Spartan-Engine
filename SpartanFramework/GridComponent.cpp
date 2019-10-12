#include "stdafx.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Grid.h"

GridComponent::GridComponent() : m_pGrid(nullptr)
{
}

GridComponent::~GridComponent()
{
	if (m_pGrid)
	{
		delete m_pGrid;
		m_pGrid = nullptr;
	}
}

void GridComponent::SetGrid(BaseGrid* pGrid)
{
	m_pGrid = pGrid;
}

BaseGrid *GridComponent::GetGrid()
{
	return m_pGrid;
}

void GridComponent::Initialize(const GameContext &)
{
}

void GridComponent::Update(const GameContext &)
{
}

void GridComponent::Draw(const GameContext &gameContext)
{
#ifdef _DEBUG
	m_pGrid->RenderGrid(gameContext, GetGameObject()->GetTransform()->GetWorldPosition());
#endif // _DEBUG
}
