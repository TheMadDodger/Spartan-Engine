#pragma once
#include <GameScene.h>
class BehaviourTreeTestScene : public GameScene
{
public:
	BehaviourTreeTestScene();
	virtual ~BehaviourTreeTestScene();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);
};

