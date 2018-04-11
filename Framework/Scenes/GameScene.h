#pragma once

class GameObject;
class BasicCamera;

class GameScene
{
public:
	GameScene(const std::string &name);
	virtual ~GameScene();

	void AddChild(GameObject *pObject);
	void SetActiveCamera(CameraComponent *pCamera);
	CameraComponent *GetActiveCamera() { return m_pActiveCamera; }

protected:
	friend class BaseGame;
	friend class SceneManager;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);
	void RootOnActive(const GameContext &gameContext);
	void RootOnDeActive(const GameContext &gameContext);

	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void OnActive(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void OnDeActive(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

private:
	friend class SceneManager;
	std::vector<GameObject*> m_pChildren;
	std::string m_SceneName = "";
	BasicCamera *m_pDefaultCamera = nullptr;
	CameraComponent *m_pActiveCamera = nullptr;
};

