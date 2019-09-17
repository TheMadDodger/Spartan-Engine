#pragma once
#include <GameScene.h>

class FreeCamera;
class GridComponent;
class AStarPathFinding;
class BaseGridNode;

class GridTestScene : public GameScene
{
public:
	GridTestScene();
	virtual ~GridTestScene();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void PostInitialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);

private:
	FreeCamera *m_pCamera;
	GridComponent *m_pGrid;
	AStarPathFinding *m_pAStarPathFinding;
	BaseGridNode *m_pStartNode;
	BaseGridNode *m_pEndNode;
};

