#pragma once
#include "ApplicationStructs.h"
#include "Framework.h"

struct SDL_Window;

class BaseGame
{
public:
	BaseGame(const GameSettings &settings);
	virtual ~BaseGame();

	virtual bool RootInitialize() final;
	virtual bool RootGameUpdate() final;
	virtual void RootGamePaint() final;

	virtual void Initialize(const GameContext &gameContext) = 0;
	virtual void GameUpdate(const GameContext &gameContext) = 0;
	virtual void GamePaint(const GameContext &gameContext) = 0;

	void QuitGame() { m_bQuitGame = true; }

	GameSettings &GetGameSettings() { return m_GameSettings; }
	const GameContext &GetGameContext() { return m_GameContext; }

	static BaseGame *GetGame() { return m_pGame; }

private:
	friend class TextureLoader;
	static BaseGame *m_pGame;
	static void SetGame(BaseGame *pGame) { m_pGame = pGame; }

private:
	GameSettings m_GameSettings;
	GameContext m_GameContext;

	bool m_bQuitGame = false;
};

