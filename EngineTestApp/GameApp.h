#pragma once

#include <BaseGame.h>

class Blackboard;

class GameApp : public BaseGame
{
public:
	GameApp(const GameSettings &settings);
	~GameApp();

	// User defined application methods
	void Initialize(const GameContext &gameContext) override;
	void GameUpdate(const GameContext &gameContext) override;
	void GamePaint(const GameContext &gameContext) override;

	virtual void RegisterPrefabs(std::vector<GameObject*> &) override {};

private:
	
};

