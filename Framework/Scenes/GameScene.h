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

	b2World *GetPhysicsWorld() { return m_pPhysicsWorld; }

protected:
	friend class BaseGame;
	friend class SceneManager;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);
	void RootOnActive(const GameContext &gameContext);
	void RootOnDeActive(const GameContext &gameContext);

	virtual void PreInitialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostInitialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	virtual void PreUpdate(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostUpdate(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	virtual void PreDraw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostDraw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	
	virtual void OnActive(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void OnDeActive(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

private:
	friend class SceneManager;
	std::vector<GameObject*> m_pChildren;
	std::string m_SceneName = "";
	BasicCamera *m_pDefaultCamera = nullptr;
	CameraComponent *m_pActiveCamera = nullptr;
	b2World *m_pPhysicsWorld = nullptr;
	b2Vec2 m_Gravity;
};

