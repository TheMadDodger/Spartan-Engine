#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class BaseGrid;

	class GridComponent : public BaseComponent
	{
	public:
		GridComponent();
		virtual ~GridComponent();

		void SetGrid(BaseGrid* pGrid);
		BaseGrid* GetGrid();

	private:
		COMPONENT_EDITOR(GridComponent)

			virtual void Initialize(const GameContext& gameContext);
		virtual void Update(const GameContext& gameContext);
		virtual void Draw(const GameContext& gameContext);

	private:
		BaseGrid* m_pGrid;
	};
}