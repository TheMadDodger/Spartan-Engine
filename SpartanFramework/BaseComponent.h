#pragma once
#include "stdafx.h"
#include "SerializedObject.h"
#include "SerializedProperty.h"

#define COMPONENT_EDITOR(comp) const std::type_info &GetType() override \
{ \
	return typeid(comp); \
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

	class BaseComponent : public Serialization::SerializedObject
	{
	public:
		BaseComponent(const char* name = "BaseComponent");
		virtual ~BaseComponent();

		GameObject* GetGameObject() const { return m_pGameObject; }

		virtual BaseComponent* Create() = 0;
		static void Register(BaseComponent* pComponent);
		static BaseComponent* CreateFromName(const std::string& name);

		const std::string& GetName() { return m_Name; }

		virtual void CustomEditor() {};

		bool IsInitialized() { return m_bInitialized; }
		bool IsEnabled() { return m_bEnabled; }
		void SetEnabled(bool enabled) { m_bEnabled = enabled; }

		virtual const std::type_info& GetBaseType() { return typeid(BaseComponent); }
		virtual const std::type_info& GetType() { return typeid(BaseComponent); }

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

		virtual void DefineSerializedProperties(std::vector<Serialization::SerializedProperty>&) override {};

		static std::vector<BaseComponent*> m_pRegisteredComponents;
		bool m_CanTickInEditor = false;
		bool m_CanTickInGame = true;
		bool m_bEnabled = true;
		bool m_bInitialized = false;

	private:
		friend class EditorApp;
		friend class GameObject;
		friend class Spartan::UI::UIObject;
		friend class Spartan::UI::Canvas;
		void SetGameObject(GameObject* pObject);
		GameObject* m_pGameObject = nullptr;

		std::string m_Name;
	};

}