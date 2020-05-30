#pragma once
#include <GameScene.h>
class BehaviourTreeTestScene : public SpartanEngine::GameScene
{
public:
	BehaviourTreeTestScene();
	virtual ~BehaviourTreeTestScene();

private:
	virtual void Initialize(const SpartanEngine::GameContext &gameContext);
	virtual void Update(const SpartanEngine::GameContext &gameContext);
	virtual void Draw(const SpartanEngine::GameContext &gameContext);
};

