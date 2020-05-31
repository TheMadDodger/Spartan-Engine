#pragma once

#include <BaseGame.h>

class Blackboard;

class GameApp : public SpartanEngine::BaseGame
{
public:
	GameApp(const SpartanEngine::GameSettings &settings);
	~GameApp();

	// User defined application methods
	void Initialize(const SpartanEngine::GameContext &gameContext) override;
	void GameUpdate(const SpartanEngine::GameContext &gameContext) override;
	void GamePaint(const SpartanEngine::GameContext &gameContext) override;

	virtual void RegisterPrefabs(std::vector<SpartanEngine::GameObject*> &) override {};
};

