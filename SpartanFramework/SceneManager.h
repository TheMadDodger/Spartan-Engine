#pragma once
#include "Manager.h"

namespace SpartanEngine
{
	class GameScene;

	enum LoadSceneFlags : int
	{
		NoFlags = 0,
		UnloadLoadedScene = 0x01,
		EnableNewSceneAfterLoad = 0x02,
	};

	class SceneManager : Manager
	{
	public: // Methods
		GameScene* GetCurrentScene() const;
		void AddScene(GameScene* pScene);
		void LoadScene(int sceneIndex, int flags = UnloadLoadedScene | EnableNewSceneAfterLoad);
		void LoadScene(const std::string& sceneName, int flags = UnloadLoadedScene | EnableNewSceneAfterLoad);
		void LoadSceneNextFrame(const std::string& sceneName);

	public: // Singleton
		static SceneManager* GetInstance();
		static void Destroy();

	private:
		void Initialize(const GameContext& gameContext);
		void Update(const GameContext& gameContext);
		void Draw(const GameContext& gameContext);

		std::vector<GameScene*> m_pScenes;
		std::vector<int> m_AdditiveScenes;
		int m_CurrentScene = 0;
		static SceneManager* m_pSceneManager;
		bool m_SceneHasInitialized = false;
		std::string m_ToLoadNextFrame = "";

	private:
		friend class BaseGame;
		friend class GameTool;
		SceneManager();
		~SceneManager();
	};
}