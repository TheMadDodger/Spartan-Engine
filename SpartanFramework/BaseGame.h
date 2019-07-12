#pragma once
#include "ApplicationStructs.h"
#include "Framework.h"

struct SDL_Window;

#ifdef _DEBUG
class ConsoleInput;
#endif

class BaseGame
{
public:
	BaseGame(const GameSettings &settings);
	virtual ~BaseGame();

	virtual bool RootInitialize();
	virtual bool RootGameUpdate();
	virtual void RootGamePaint();

	virtual void Initialize(const GameContext &gameContext) = 0;
	virtual void GameUpdate(const GameContext &gameContext) = 0;
	virtual void GamePaint(const GameContext &gameContext) = 0;
	virtual void OnSDLEvent(SDL_Event *) {};

	void QuitGame() { m_bQuitGame = true; }

	GameSettings &GetGameSettings() { return m_GameSettings; }
	const GameContext &GetGameContext() { return m_GameContext; }

	static BaseGame *GetGame() { return m_pGame; }

#ifdef _DEBUG
protected:
	virtual void RegisterConsoleCommands(ConsoleInput *) {}
#endif // _DEBUG

private:
	friend class TextureLoader;
	static BaseGame *m_pGame;
	static void SetGame(BaseGame *pGame) { m_pGame = pGame; }

private:
	friend class GameTool;
	GameSettings m_GameSettings;
	GameContext m_GameContext;

#ifdef _DEBUG
	ConsoleInput *m_pConspole;
#endif

	bool m_bQuitGame = false;
};

