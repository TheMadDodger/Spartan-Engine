#pragma once
#include "ApplicationStructs.h"
#include "Framework.h"
#include "SEObject.h"

struct SDL_Window;

namespace Spartan
{
	class GameObject;
	class LayerManager;

#ifdef _DEBUG
	class ConsoleInput;
#endif

	class BaseGame
	{
	public:
		BaseGame(const GameSettings& settings);
		virtual ~BaseGame();

		virtual bool RootInitialize();
		virtual bool RootGameUpdate();
		virtual void RootGamePaint();

		void ApplySettings(const GameSettings& newSettings);

		virtual void Initialize(const GameContext& gameContext) = 0;
		virtual void GameUpdate(const GameContext& gameContext) = 0;
		virtual void GamePaint(const GameContext& gameContext) = 0;
		virtual void OnSDLEvent(SDL_Event*) {};

		void QuitGame() { m_bQuitGame = true; }

		const GameSettings& GetGameSettings() const { return m_GameSettings; }
		const GameContext& GetGameContext() const { return m_GameContext; }

		static BaseGame* GetGame() { return m_pGame; }

		virtual void RegisterLayers(LayerManager*) {};
		virtual void RegisterPrefabs(std::vector<GameObject*>& prefabs) = 0;
		virtual void RegisterAssets() {}
		virtual void RegisterComponents() {};

#ifdef _DEBUG
	protected:
		virtual void RegisterConsoleCommands(ConsoleInput*) {}
#endif // _DEBUG

	private:
		friend class TextureLoader;
		friend class EditorApp;
		static BaseGame* m_pGame;
		static void SetGame(BaseGame* pGame) { m_pGame = pGame; }

		void HandleWindowEvent(SDL_Event* event);

		void RegisterCoreComponents();

	protected:
		friend class EditorApp;
		GameSettings m_GameSettings;
		GameContext m_GameContext;
		std::vector<GameObject*> m_pPrefabs;

	private:
#ifdef _DEBUG
		ConsoleInput* m_pConspole;
#endif

		bool m_bQuitGame = false;
	};
}