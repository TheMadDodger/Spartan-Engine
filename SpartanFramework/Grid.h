#pragma once
#include "Node.h"

namespace Spartan
{
	class BaseGridNode : Node
	{
	public:
		BaseGridNode(const Vector2& worldPosition) : m_WorldPosition(worldPosition) {}
		virtual ~BaseGridNode() {}

		void SetParentNode(BaseGridNode* pParent)
		{
			m_pParent = pParent;
		}

		BaseGridNode* GetParentNode()
		{
			return m_pParent;
		}

		virtual Color GetNodeColor()
		{
			return Color::White();
		}

		virtual void Render(const GameContext& gameContext, const Vector2& drawSize, const Vector2& rootPosition, const Color& color)
		{
			Vector2 actualDrawSize = drawSize;
			actualDrawSize = actualDrawSize - Vector2(1.0f, 1.0f);
			Vector2 renderPosition = (Vector2&)m_WorldPosition - rootPosition;
			gameContext.pRenderer->DrawSolidRect(renderPosition - actualDrawSize / 2.0f, renderPosition + actualDrawSize / 2.0f, color);
		}

	public:
		const Vector2 m_WorldPosition;
		BaseGridNode* m_pParent = nullptr;
	};

	class Base2DGridNode : public BaseGridNode
	{
	public:
		Base2DGridNode(const IntVector2& coord, const Vector2& worldPosition) : m_Coord(coord), BaseGridNode(worldPosition) {}
		virtual ~Base2DGridNode() {}

	public:
		const IntVector2 m_Coord;
	};

	class BaseGrid : SEObject
	{
	public:
		BaseGrid(size_t size, const Vector2& cellSize) : m_Size(size), m_GridCellSize(cellSize)
		{
			m_GridNodes = new BaseGridNode * [size];
			for (size_t i = 0; i < m_Size; i++)
			{
				m_GridNodes[i] = nullptr;
			}
		}

		~BaseGrid()
		{
			for (size_t i = 0; i < m_Size; i++)
			{
				if (m_GridNodes[i] != nullptr)
				{
					delete m_GridNodes[i];
				}
			}
			delete[] m_GridNodes;
		}

		virtual vector<BaseGridNode*> GetNeighbours(BaseGridNode* start) = 0;
		virtual int GetDistance(BaseGridNode* nodeA, BaseGridNode* nodeB) = 0;
		virtual BaseGridNode* GetNodeAtWorldPosition(const Vector2& worldPosition) = 0;

		virtual void RenderGrid(const GameContext& gameContext, const Vector2& rootPosition)
		{
			for (size_t i = 0; i < m_Size; i++)
			{
				if (m_GridNodes[i] == nullptr) continue;
				m_GridNodes[i]->Render(gameContext, m_GridCellSize, rootPosition, m_GridNodes[i]->GetNodeColor());
			}
		}

	protected:
		void SetNode(int index, BaseGridNode* node)
		{
			if (!CheckIndex(index)) return;
			m_GridNodes[index] = node;
		}

		BaseGridNode* GetNode(int index)
		{
			if (!CheckIndex(index)) return nullptr;
			return m_GridNodes[index];
		}

	private:
		bool CheckIndex(size_t index)
		{
			if (index < 0 || index >= m_Size)
			{
				throw new exception("Index out of range!");
				return false;
			}
			return true;
		}

	protected:
		const size_t m_Size;
		BaseGridNode** m_GridNodes;
		const Vector2 m_GridCellSize;
	};

	class Grid2D : public BaseGrid
	{
	public:
		Grid2D(size_t width, size_t height, const Vector2& cellSize)
			: m_Width(width), m_Height(height), m_Size(width* height),
			m_GridWorldSize((Vector2&)m_GridCellSize* Vector2((float)width, (float)height)),
			BaseGrid(width* height, cellSize) {}
		virtual ~Grid2D() {}

	public:
		void SetNode(int x, int y, Base2DGridNode* node)
		{
			int index = CalculateIndex(x, y);
			BaseGrid::SetNode(index, node);
		}

		Base2DGridNode* GetNode(const IntVector2& coord)
		{
			return GetNode(coord.x, coord.y);
		}

		Base2DGridNode* GetNode(int x, int y)
		{
			int index = CalculateIndex(x, y);
			return (Base2DGridNode*)BaseGrid::GetNode(index);
		}

		bool IsValidCoord(IntVector2 coord)
		{
			return IsValidCoord(coord.x, coord.y);
		}

		bool IsValidCoord(size_t x, size_t y)
		{
			if (x < 0 || x >= m_Width) return false;
			if (y < 0 || y >= m_Width) return false;
			return true;
		}

		size_t GetWidth()
		{
			return m_Width;
		}

		size_t GetHeight()
		{
			return m_Height;
		}

		template<typename T>
		void Generate()
		{
			for (size_t x = 0; x < m_Width; x++)
			{
				for (size_t y = 0; y < m_Height; y++)
				{
					IntVector2 coord = IntVector2(x, y);
					IntVector2 halfCoord = coord - IntVector2(m_Width / 2, m_Height / 2);
					Vector2 worldPosition = (Vector2&)m_GridCellSize * halfCoord;
					T* pNewNode = new T(coord, worldPosition);
					SetNode(coord.x, coord.y, (Base2DGridNode*)pNewNode);
				}
			}
		}

	protected:
		virtual vector<BaseGridNode*> GetNeighbours(BaseGridNode* start) override
		{
			Base2DGridNode* pStartNode = (Base2DGridNode*)start;
			vector<BaseGridNode*> neighbours;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					if (x == 0 && y == 0) continue;

					IntVector2 checkCoord = pStartNode->m_Coord;
					checkCoord = checkCoord + IntVector2(x, y);
					if (!IsValidCoord(checkCoord)) continue;
					Base2DGridNode* node = GetNode(checkCoord.x, checkCoord.y);
					if (node == nullptr) continue;
					neighbours.push_back(node);
				}
			}
			return neighbours;
		}

		virtual int GetDistance(BaseGridNode* nodeA, BaseGridNode* nodeB) override
		{
			Base2DGridNode* node2DA = (Base2DGridNode*)nodeA;
			Base2DGridNode* node2DB = (Base2DGridNode*)nodeB;

			IntVector2 diff = (IntVector2&)node2DB->m_Coord - node2DA->m_Coord;
			if (diff.x != 0) Math::Absolute<int>(diff.x);
			if (diff.y != 0) Math::Absolute<int>(diff.y);

			if (diff.x > diff.y) return DISTANCE_DIAGONAL * diff.y + DISTANCE_STRAIGHT * (diff.x - diff.y);
			return DISTANCE_DIAGONAL * diff.x + DISTANCE_STRAIGHT * (diff.y - diff.x);
		}

		virtual BaseGridNode* GetNodeAtWorldPosition(const Vector2& worldPosition) override
		{
			Vector2 percent = ((Vector2&)worldPosition + (Vector2&)m_GridWorldSize / 2.0f) / m_GridWorldSize;
			percent.x = Clamp<float>(0.0f, 1.0f, percent.x);
			percent.y = Clamp<float>(0.0f, 1.0f, percent.y);

			IntVector2 coord;
			coord.x = (int)((m_Width - 1) * percent.x);
			coord.y = (int)((m_Height - 1) * percent.y);
			return GetNode(coord);
		}

	private:
		int CalculateIndex(int x, int y)
		{
			return y * m_Width + x;
		}

	private:
		const size_t m_Width;
		const size_t m_Height;
		const size_t m_Size;
		const Vector2 m_GridWorldSize;

		const int DISTANCE_STRAIGHT = 10;
		const int DISTANCE_DIAGONAL = 14;
	};
}