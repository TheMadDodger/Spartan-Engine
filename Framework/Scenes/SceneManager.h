#pragma once

class GameScene;

class SceneManager
{
public: // Methods
	GameScene * GetCurrentScene() const;
	void AddScene(GameScene *pScene);
	void LoadScene(int sceneIndex);
	void LoadScene(const std::string &sceneName);

public: // Singleton
	static SceneManager *GetInstance();
	static void Destroy();

private:
	void Initialize(const GameContext &gameContext);
	void Update(const GameContext &gameContext);
	void Draw(const GameContext &gameContext);

	std::vector<GameScene*> m_pScenes;
	int m_CurrentScene = 0;
	static SceneManager *m_pSceneManager;
	bool m_SceneHasInitialized = false;

private:
	friend class BaseGame;
	SceneManager();
	~SceneManager();
};

