#pragma once
#include "Grid.h"
#include "Node.h"

namespace SpartanEngine
{
	class IAStarPathNode : Node
	{
	public:
		IAStarPathNode() : m_HCost(0), m_GCost(0), m_Moveable(true), m_MovementPenalty(0) {};
		virtual ~IAStarPathNode() {}

	public:
		virtual void SetCosts(int hCost, int gCost);
		virtual int GetHCost();
		virtual int GetGCost();
		virtual int GetFCost();
		virtual bool IsMoveable();
		virtual void SetMoveable(bool moveable);

	protected:
		int m_MovementPenalty = 0;
		int m_HCost = 0;
		int m_GCost = 0;
		bool m_Moveable = true;
	};

	//class AStarWaypointNode : public BaseGridNode, public IAStarPathNode
	//{
	//public:
	//	AStarWaypointNode();
	//	virtual ~AStarWaypointNode();
	//};

	class AStar2DGridNode : public Base2DGridNode, public IAStarPathNode
	{
	public:
		AStar2DGridNode(const IntVector2& coord, const Vector2& worldPosition) : Base2DGridNode(coord, worldPosition), IAStarPathNode() {}
		virtual ~AStar2DGridNode() {}

	private:
		virtual Color GetNodeColor() override;
	};
}