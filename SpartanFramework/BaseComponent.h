#pragma once
#include "stdafx.h"

class GameObject;

#define COMPONENT_EDITOR const std::type_info &GetType() override \
{ \
	return typeid(this); \
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

protected:
	friend class GameObject;
	void RootInitialize(const GameContext &gameContext);
	void RootUpdate(const GameContext &gameContext);
	void RootDraw(const GameContext &gameContext);

	virtual void Initialize(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Update(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };
	virtual void Draw(const GameContext &gameContext) { UNREFERENCED_PARAMETER(gameContext); };

	static std::vector<BaseComponent*> m_pRegisteredComponents;

private:
	friend class GameObject;
	void SetGameObject(GameObject *pObject);
	GameObject *m_pGameObject = nullptr;

	std::string m_Name;
};
