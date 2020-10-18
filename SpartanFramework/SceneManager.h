#pragma once
#include "Singleton.h"
#include "GameScene.h"

namespace Spartan
{
	struct Scene
	{
	public:
		Scene(const std::string& path, const std::string& name, int buildIndex);

		const std::string m_Path;
		const std::string m_Name;
		const int m_BuildIndex;
	};

	enum LoadSceneMode
	{
		Single,
		Additive
	};

	struct LoadOperation
	{
	public:
		LoadOperation(LoadSceneMode mode, size_t buildIndex, bool unload = false);

		LoadSceneMode m_Mode;
		size_t m_BuildIndex;
		bool m_Unload;
	};

	class SceneManager : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		virtual ~SceneManager();

	public: // Methods
		GameScene* GetActiveScene() const;
		void LoadScene(size_t buildIndex, LoadSceneMode mode = LoadSceneMode::Single);
		void LoadScene(const std::string& sceneName, LoadSceneMode mode = LoadSceneMode::Single);

	private:
		void Initialize(const GameContext& gameContext);
		void Update(const GameContext& gameContext);
		void Draw(const GameContext& gameContext);
		void UnloadAll();
		void HandleLoadOperation(const LoadOperation& operation);
		void HandleUnLoadOperation(const LoadOperation& operation);

	private:
		std::vector<GameScene*> m_pLoadedScenes;
		GameScene* m_pActiveScene;
		std::vector<Scene> m_BuildScenes;

		std::queue<LoadOperation> m_LoadOperations;

	private:
		friend class BaseGame;
		friend class EditorApp;
	};
}