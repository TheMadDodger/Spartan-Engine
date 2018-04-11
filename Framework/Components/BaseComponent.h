#pragma once
class GameObject;

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	GameObject *GetGameObject() { return m_pGameObject; }

protected:
	friend class GameObject;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);

	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

private:
	friend class GameObject;
	void SetGameObject(GameObject *pObject);
	GameObject *m_pGameObject = nullptr;
};

