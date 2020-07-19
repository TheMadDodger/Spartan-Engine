#pragma once
#include "stdafx.h"

#define COMPONENT_EDITOR(comp) const std::type_info &GetType() override \
{ \
	return typeid(this); \
} \
virtual BaseComponent *Create() override \
{ \
	return new comp; \
}

namespace Spartan
{
	namespace UI
	{
		class UIObject;
		class Canvas;
	}
}

namespace Spartan
{
	class GameObject;

	class BaseComponent : SEObject
	{
	public:
		BaseComponent(const char* name = "BaseComponent");
		virtual ~BaseComponent();

		GameObject* GetGameObject() const { return m_pGameObject; }

		virtual BaseComponent* Create() = 0;
		static void Register(BaseComponent* pComponent);
		static BaseComponent* CreateFromName(const std::string& name);

		const std::string& GetName() { return m_Name; }

		virtual const std::type_info& GetType() { return typeid(this); }

		virtual void CustomEditor() {};

		bool IsInitialized() { return m_bInitialized; }
		bool IsEnabled() { return m_bEnabled; }
		void SetEnabled(bool enabled) { m_bEnabled = enabled; }

	protected:
		friend class GameObject;
		virtual void RootAwake();
		virtual void RootInitialize(const GameContext& gameContext);
		virtual void RootUpdate(const GameContext& gameContext);
		virtual void RootDraw(const GameContext& gameContext);

		virtual void Awake() {};
		virtual void Initialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void PostInitialize(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void Update(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void Draw(const GameContext& gameContext) { UNREFERENCED_PARAMETER(gameContext); };
		virtual void OnDestroy() { }

		static std::vector<BaseComponent*> m_pRegisteredComponents;
		bool m_CanTickInEditor = false;
		bool m_CanTickInGame = true;
		bool m_bEnabled = true;
		bool m_bInitialized = false;

	private:
		friend class GameObject;
		friend class Spartan::UI::UIObject;
		friend class Spartan::UI::Canvas;
		void SetGameObject(GameObject* pObject);
		GameObject* m_pGameObject = nullptr;

		std::string m_Name;
	};

}