#pragma once
#include "GameObject.h"
#include "Layers.h"

class BasicCamera;

const int Box2DVelocityIterations = 6; // How many velocity iterations should Box2D per game tick perform?
const int Box2DPositionIterations = 2; // How many position iterations should Box2D per game tick perform?
const int FixedUpdateSpeed = 60; // Used for Box2D ticks

class GameScene : SEObject
{
public:
	GameScene(const std::string &name);
	virtual ~GameScene();

	void SetActiveCamera(CameraComponent *pCamera);
	CameraComponent *GetActiveCamera() { return m_pActiveCamera; }

	b2World *GetPhysicsWorld() const { return m_pPhysicsWorld; }

	const std::string &GetName() const { return m_SceneName; }

	void DontDestroyOnLoad(GameObject *pObject);

	std::vector<GameObject*> GetChildren() { return m_pChildren; }
	GameObject *GetChild(unsigned int ID) { return m_pChildren[ID]; }

	void Destroy(GameObject *gameObject);

	template<class T>
	T *Instantiate(GameObject* pParent = nullptr)
	{
		T* pT = new T();
		GameObject* pObject = dynamic_cast<GameObject*>(pT);
		if (pObject == nullptr)
		{
			Utilities::Debug::LogError("Can not instantiate a class that does not derive from GameObject!");
			return nullptr;
		}

		pObject->m_pScene = this;
		if (pParent != nullptr)
		{
			pParent->AddChild(pObject);
			return nullptr;
		}

		AddChild(pObject);
		UpdateLayers(pObject, -1, pObject->GetLayer().LayerID);
		return pT;
	}

	void SetEnabled(bool enabled);
	

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
	void RenderLayer(const GameContext& gameContext, std::list<GameObject*> pObjectsOnLayer);

	void LoadPersistent();

	void RootOnActive();
	void RootOnDeActive();

	void RootCleanup();

	void UpdateLayers(GameObject* pObject, int oldLayer, int newLayer);

	void AddChild(GameObject* pObject);
	void RemoveChild(GameObject* pObject);

private:
	friend class SceneManager;
	friend class GameObject;

	std::vector<GameObject*> m_pChildren;
	std::vector<std::list<GameObject*>> m_pLayers;
	std::vector<GameObject*> m_pPersistentChildren;
	std::string m_SceneName = "";
	BasicCamera *m_pDefaultCamera = nullptr;
	CameraComponent *m_pActiveCamera = nullptr;
	b2World *m_pPhysicsWorld = nullptr;
	b2Vec2 m_Gravity;
	bool m_bEnabled = false;
};

