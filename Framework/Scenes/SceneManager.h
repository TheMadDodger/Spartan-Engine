#pragma once

class GameScene;

class SceneManager
{
public:
	GameScene * GetCurrentScene() const;
	void AddScene(GameScene *pScene);

	static SceneManager *GetInstance();
	static void Destroy();

private:
	void Initialize(const GameContext &gameContext);
	void Update(const GameContext &gameContext);
	void Draw(const GameContext &gameContext);

	std::vector<GameScene*> m_pScenes;
	int m_CurrentScene = 0;
	static SceneManager *m_pSceneManager;

private:
	friend class BaseGame;
	SceneManager();
	~SceneManager();
};

