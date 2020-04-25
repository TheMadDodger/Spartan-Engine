#pragma once
#include "Grid.h"
#include "SEObject.h"

namespace SpartanEngine
{
	class IAStarPathNode;

	class AStarPathFinding : SEObject
	{
	public:
		AStarPathFinding(BaseGrid* pGrid) : m_pGrid(pGrid) {}
		~AStarPathFinding() {}

		void FindPath(BaseGridNode* start, BaseGridNode* end, bool simplify = true);

		static vector<BaseGridNode*> GetPath()
		{
			return m_Path;
		}

		static BaseGridNode* m_SelectedNode;

	private:
		void RetracePath(BaseGridNode* startNode, BaseGridNode* endNode, vector<BaseGridNode*>& path);
		void SimplifyPath(const vector<BaseGridNode*>& path, vector<BaseGridNode*>& finalPath);

	private:
		BaseGrid* m_pGrid = nullptr;
		static vector<BaseGridNode*> m_Path;
	};
}