#pragma once
#include "stdafx.h"

class GameObject;

#define COMPONENT_EDITOR(comp) const std::type_info &GetType() override \
{ \
	return typeid(this); \
} \
virtual BaseComponent *Create() override \
{ \
	return new comp; \
}

class BaseComponent
{
public:
	BaseComponent(const char *name = "BaseComponent");
	virtual ~BaseComponent();

	GameObject *GetGameObject() { return m_pGameObject; }

	virtual BaseComponent *Create() = 0;
	static void Register(BaseComponent *pComponent);
	static BaseComponent *CreateFromName(const std::string &name);

	const std::string &GetName() { return m_Name; }

	virtual const std::type_info &GetType() { return typeid(this); }

	virtual void CustomEditor() {};

protected:
	friend class GameObject;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);
	void RootCleanup();

	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void PostInitialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Cleanup() { }

	static std::vector<BaseComponent*> m_pRegisteredComponents;
	bool m_CanTickInEditor = false;
	bool m_CanTickInGame = true;

private:
	friend class GameObject;
	void SetGameObject(GameObject *pObject);
	GameObject *m_pGameObject = nullptr;
	bool m_bInitialized = false;

	std::string m_Name;
};

