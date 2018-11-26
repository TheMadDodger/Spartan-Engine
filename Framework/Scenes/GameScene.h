#pragma once

class GameObject;
class BasicCamera;

const int Box2DVelocityIterations = 6; // How many velocity iterations should Box2D per game tick perform?
const int Box2DPositionIterations = 2; // How many position iterations should Box2D per game tick perform?
const int FixedUpdateSpeed = 60; // Used for Box2D ticks

class GameScene
{
public:
	GameScene(const std::string &name);
	virtual ~GameScene();

	void AddChild(GameObject *pObject);
	void SetActiveCamera(CameraComponent *pCamera);
	CameraComponent *GetActiveCamera() { return m_pActiveCamera; }

	b2World *GetPhysicsWorld() const { return m_pPhysicsWorld; }

	const std::string &GetName() const { return m_SceneName; }

	void DontDestroyOnLoad(GameObject *pObject);

protected:
	friend class BaseGame;
	friend class SceneManager;

	virtual void PreInitialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostInitialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	virtual void GameStart(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	virtual void PreUpdate(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostUpdate(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	virtual void PreDraw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostDraw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	
	virtual void OnActive() { };
	virtual void OnDeActive() { };

	virtual void Cleanup() {};

private:
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);

	void LoadPersistent();

	void RootOnActive();
	void RootOnDeActive();

	void RootCleanup();

private:
	friend class SceneManager;
	std::vector<GameObject*> m_pChildren;
	std::vector<GameObject*> m_pPersistentChildren;
	std::string m_SceneName = "";
	BasicCamera *m_pDefaultCamera = nullptr;
	CameraComponent *m_pActiveCamera = nullptr;
	b2World *m_pPhysicsWorld = nullptr;
	b2Vec2 m_Gravity;
};

