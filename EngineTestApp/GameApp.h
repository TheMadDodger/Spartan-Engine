#pragma once

#include <BaseGame.h>

class Blackboard;

class GameApp : public Spartan::BaseGame
{
public:
	GameApp(const Spartan::GameSettings &settings);
	virtual ~GameApp();

	// User defined application methods
	void Initialize(const Spartan::GameContext &gameContext) override;
	void GameUpdate(const Spartan::GameContext &gameContext) override;
	void GamePaint(const Spartan::GameContext &gameContext) override;

	virtual void RegisterPrefabs(std::vector<Spartan::GameObject*> &) override {};
};

