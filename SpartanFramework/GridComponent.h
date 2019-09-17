#pragma once
#include "BaseComponent.h"

class BaseGrid;

class GridComponent : public BaseComponent
{
public:
	GridComponent(BaseGrid *pGrid);
	virtual ~GridComponent();

	BaseGrid *GetGrid();

	virtual BaseComponent *Create() override { return new GridComponent(nullptr); }

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);

private:
	BaseGrid *m_pGrid;
};
