#include "stdafx.h"
#include "PathFindingNodes.h"
#include "AStarPathFinding.h"

namespace SpartanEngine
{
	Color AStar2DGridNode::GetNodeColor()
	{
		if (!m_Moveable) return Color::Red();
		auto path = AStarPathFinding::GetPath();
		if (AStarPathFinding::m_SelectedNode == this) return Color::Cyan();
		if (std::find(path.begin(), path.end(), this) != path.end()) return Color::Green();
		return Color::White();
	}

	void IAStarPathNode::SetCosts(int hCost, int gCost)
	{
		m_HCost = hCost;
		m_GCost = gCost;
	}

	int IAStarPathNode::GetHCost()
	{
		return m_HCost;
	}

	int IAStarPathNode::GetGCost()
	{
		return m_GCost;
	}

	int IAStarPathNode::GetFCost()
	{
		return m_HCost + m_GCost + m_MovementPenalty;
	}

	bool IAStarPathNode::IsMoveable()
	{
		return m_Moveable;
	}

	void IAStarPathNode::SetMoveable(bool moveable)
	{
		m_Moveable = moveable;
	}
}