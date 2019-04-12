#pragma once
#include <GameScene.h>
class GUIDTestScene : public GameScene
{
public:
	GUIDTestScene();
	virtual ~GUIDTestScene();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);
};

