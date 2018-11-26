#pragma once
#include "../ApplicationStructs.h"
#include "../Components/BaseComponent.h"

class TransformComponent;
class GameScene;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void AddChild(GameObject *pChild, bool initialize = false);
	void RemoveChild(GameObject *pChild, bool deleteObject = false);

	const vector<BaseComponent*> GetAllComponents() { return m_pComponents; }

	template <typename T>
	vector<T*> GetComponents()
	{
		vector<BaseComponent*> pComponents;
		for (auto pComponent : m_pComponents)
		{
			if (typeid(pComponent) == typeid(T))
			{
				pComponents.push_back(pComponent);
			}
		}
		return pComponents;
	}

	template <typename T>
	T *GetComponent()
	{
		for (auto pComponent : m_pComponents)
		{
			T *pComp = dynamic_cast<T*>(pComponent);
			if(pComp != nullptr)
			{
				return pComp;
			}
		}

		return nullptr;
	}

	TransformComponent *GetTransform() const { return m_pTransform; }
	BaseComponent *AddComponent(BaseComponent *pComponent);
	GameScene *GetGameScene() const;
	GameObject *GetChild(size_t index);
	const vector<GameObject*> &GetChildren();
	//template <typename T>
	//T* GetChildren();

	GameObject *GetParent() { return m_pParentObject; }

	const std::string &GetTag();
	void SetTag(const std::string &tag);

	bool IsEnabled();
	void SetEnabled(bool enabled);

protected:
	friend class GameScene;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);
	void SetParent(GameObject *pParent);

	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); }
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); }
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); }

private:
	friend class GameScene;
	TransformComponent *m_pTransform = nullptr;
	std::vector<BaseComponent*> m_pComponents;
	GameScene *m_pScene = nullptr;
	vector<GameObject*> m_pChildren;
	GameObject *m_pParentObject = nullptr;
	bool m_bInitialized = false;
	bool m_Enabled = true;
	std::string m_Tag;

	bool m_Persistent = false;
};

