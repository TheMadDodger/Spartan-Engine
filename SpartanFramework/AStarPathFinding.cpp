#include "stdafx.h"
#include "AStarPathFinding.h"
#include "PathFindingNodes.h"

namespace SpartanEngine
{
	vector<BaseGridNode*> AStarPathFinding::m_Path = vector<BaseGridNode*>();
	BaseGridNode* AStarPathFinding::m_SelectedNode = nullptr;

	void AStarPathFinding::FindPath(BaseGridNode* start, BaseGridNode* end, bool simplify)
	{
		IAStarPathNode* startPathNode = dynamic_cast<IAStarPathNode*>(start);
		IAStarPathNode* endPathNode = dynamic_cast<IAStarPathNode*>(end);
		if (!startPathNode->IsMoveable() || !endPathNode->IsMoveable()) return;

		// Heapified open list
		vector<BaseGridNode*> openList;
		vector<BaseGridNode*> closedList;

		openList.push_back(start);

		BaseGridNode* currentNode = nullptr;
		while (openList.size() > 0)
		{
			currentNode = openList.front();
			openList.erase(openList.begin());

			pop_heap(openList.begin(), openList.end(), [&](BaseGridNode* pNodeA, BaseGridNode* pNodeB)
			{
				IAStarPathNode* pathNodeA = dynamic_cast<IAStarPathNode*>(pNodeA);
				IAStarPathNode* pathNodeB = dynamic_cast<IAStarPathNode*>(pNodeB);

				if (pathNodeA->GetFCost() == pathNodeB->GetFCost())
					return (pathNodeA->GetHCost() > pathNodeB->GetHCost());

				return (pathNodeA->GetFCost() > pathNodeB->GetFCost());
			});

			closedList.push_back(currentNode);

			// Path is found when we are at the end node!
			if (currentNode == end)
			{
				break;
			}

			IAStarPathNode* currentPathNode = dynamic_cast<IAStarPathNode*>(currentNode);

			auto neighbours = m_pGrid->GetNeighbours(currentNode);
			for (auto neighbour : neighbours)
			{
				IAStarPathNode* pathNode = dynamic_cast<IAStarPathNode*>(neighbour);
				if (!pathNode->IsMoveable()) continue;
				if (std::find(closedList.begin(), closedList.end(), neighbour) != closedList.end()) continue;

				int costToNeighbour = currentPathNode->GetGCost() + m_pGrid->GetDistance(currentNode, neighbour);

				bool isNotInOpenList = openList.size() == 0 || (std::find(openList.begin(), openList.end(), neighbour) == openList.end());
				if (costToNeighbour < pathNode->GetGCost() || isNotInOpenList)
				{
					int newHCost = m_pGrid->GetDistance(neighbour, end);
					pathNode->SetCosts(newHCost, costToNeighbour);
					neighbour->SetParentNode(currentNode);

					if (isNotInOpenList)
					{
						openList.push_back(neighbour);
						push_heap(openList.begin(), openList.end(), [&](BaseGridNode* pNodeA, BaseGridNode* pNodeB)
						{
							IAStarPathNode* pathNodeA = dynamic_cast<IAStarPathNode*>(pNodeA);
							IAStarPathNode* pathNodeB = dynamic_cast<IAStarPathNode*>(pNodeB);

							if (pathNodeA->GetFCost() == pathNodeB->GetFCost())
								return (pathNodeA->GetHCost() > pathNodeB->GetHCost());

							return (pathNodeA->GetFCost() > pathNodeB->GetFCost());
						});
					}
				}
			}
		}

		if (simplify)
		{
			vector<BaseGridNode*> path;
			RetracePath(start, end, path);
			SimplifyPath(path, m_Path);
		}
		else
		{
			RetracePath(start, end, m_Path);
		}
	}

	void AStarPathFinding::RetracePath(BaseGridNode* startNode, BaseGridNode* endNode, vector<BaseGridNode*>& path)
	{
		path.clear();
		BaseGridNode* pCurrentNode = endNode;
		while (pCurrentNode != startNode)
		{
			if (pCurrentNode == nullptr) break;

			path.push_back(pCurrentNode);
			pCurrentNode = pCurrentNode->GetParentNode();
		}
		path.reserve(path.size());
	}

	void AStarPathFinding::SimplifyPath(const vector<BaseGridNode*>& path, vector<BaseGridNode*>& finalPath)
	{
		finalPath.clear();
		if (path.size() <= 1)
		{
			if (path.size() > 0) finalPath.push_back(path[0]);
			return;
		}
		Vector2 lastDirection = (Vector2&)path[1]->m_WorldPosition - path[0]->m_WorldPosition;
		lastDirection.Normalize();

		finalPath.push_back(path[0]);

		for (size_t i = 1; i < path.size() - 1; i++)
		{
			Vector2 newDirection = (Vector2&)path[i + 1]->m_WorldPosition - path[i]->m_WorldPosition;
			newDirection.Normalize();
			if (lastDirection != newDirection)
			{
				finalPath.push_back(path[i]);
			}
			lastDirection = newDirection;
		}

		finalPath.push_back(path[path.size() - 1]);
	}
}